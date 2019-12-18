#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int (* bsinfo ) (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ;int /*<<< orphan*/  codec_param; } ;
typedef  TYPE_1__ hb_work_object_t ;
struct TYPE_12__ {int profile; } ;
typedef  TYPE_2__ hb_work_info_t ;
struct TYPE_13__ {int /*<<< orphan*/  h; } ;
typedef  TYPE_3__ hb_stream_t ;
struct TYPE_14__ {int stream_type; scalar_t__* codec_name; int /*<<< orphan*/  codec_param; void* stream_kind; int /*<<< orphan*/  codec; int /*<<< orphan*/  stream_id; int /*<<< orphan*/  probe_buf; } ;
typedef  TYPE_4__ hb_pes_stream_t ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 void* A ; 
#define  FF_PROFILE_DTS 132 
#define  FF_PROFILE_DTS_96_24 131 
#define  FF_PROFILE_DTS_ES 130 
#define  FF_PROFILE_DTS_HD_HRA 129 
#define  FF_PROFILE_DTS_HD_MA 128 
 int /*<<< orphan*/  HB_ACODEC_DCA ; 
 char* av_get_profile_name (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * avcodec_find_decoder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* hb_audio_decoder (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_log (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,char const*,int) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int probe_dts_profile( hb_stream_t *stream, hb_pes_stream_t *pes )
{
    hb_work_info_t info;
    hb_work_object_t *w = hb_audio_decoder( stream->h, pes->codec );

    w->codec_param = pes->codec_param;
    int ret = w->bsinfo( w, pes->probe_buf, &info );
    if ( ret < 0 )
    {
        hb_log( "probe_dts_profile: no info type %d/0x%x for id 0x%x",
                pes->codec, pes->codec_param, pes->stream_id );

    }
    switch (info.profile)
    {
        case FF_PROFILE_DTS:
        case FF_PROFILE_DTS_ES:
        case FF_PROFILE_DTS_96_24:
            pes->codec = HB_ACODEC_DCA;
            pes->stream_type = 0x82;
            pes->stream_kind = A;
            break;

        case FF_PROFILE_DTS_HD_HRA:
        case FF_PROFILE_DTS_HD_MA:
            pes->stream_type = 0;
            pes->stream_kind = A;
            break;

        default:
            free(w);
            return 0;
    }
    const char *profile_name;
    AVCodec *codec = avcodec_find_decoder( pes->codec_param );
    profile_name = av_get_profile_name( codec, info.profile );
    if ( profile_name )
    {
        strncpy(pes->codec_name, profile_name, 80);
        pes->codec_name[79] = 0;
    }
    free(w);
    return 1;
}