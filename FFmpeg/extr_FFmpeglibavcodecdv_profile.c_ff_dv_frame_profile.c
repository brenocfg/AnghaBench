#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  AVDVProfile ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */

const AVDVProfile* ff_dv_frame_profile(AVCodecContext* codec, const AVDVProfile *sys,
                                       const uint8_t *frame, unsigned buf_size)
{
#if CONFIG_DVPROFILE
    int i, dsf, stype;

    if(buf_size < DV_PROFILE_BYTES)
        return NULL;

    dsf   = (frame[3] & 0x80) >> 7;
    stype = frame[80 * 5 + 48 + 3] & 0x1f;

    /* 576i50 25Mbps 4:1:1 is a special case */
    if ((dsf == 1 && stype == 0 && frame[4] & 0x07 /* the APT field */) ||
        (stype == 31 && codec && codec->codec_tag==AV_RL32("SL25") && codec->coded_width==720 && codec->coded_height==576))
        return &dv_profiles[2];

    if(   stype == 0
       && codec
       && (codec->codec_tag==AV_RL32("dvsd") || codec->codec_tag==AV_RL32("CDVC"))
       && codec->coded_width ==720
       && codec->coded_height==576)
        return &dv_profiles[1];

    for (i = 0; i < FF_ARRAY_ELEMS(dv_profiles); i++)
        if (dsf == dv_profiles[i].dsf && stype == dv_profiles[i].video_stype)
            return &dv_profiles[i];

    /* check if old sys matches and assumes corrupted input */
    if (sys && buf_size == sys->frame_size)
        return sys;

    /* hack for trac issue #217, dv files created with QuickTime 3 */
    if ((frame[3] & 0x7f) == 0x3f && frame[80 * 5 + 48 + 3] == 0xff)
        return &dv_profiles[dsf];
#endif

    return NULL;
}