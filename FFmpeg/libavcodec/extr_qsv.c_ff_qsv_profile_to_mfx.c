#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_3__ {int codec_id; int codec_profile; int mfx_profile; } ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_1__*) ; 
 int FF_PROFILE_UNKNOWN ; 
 int MFX_PROFILE_UNKNOWN ; 
 TYPE_1__* qsv_profile_map ; 

int ff_qsv_profile_to_mfx(enum AVCodecID codec_id, int profile)
{
    int i;
    if (profile == FF_PROFILE_UNKNOWN)
        return MFX_PROFILE_UNKNOWN;

    for (i = 0; i < FF_ARRAY_ELEMS(qsv_profile_map); i++) {
        if (qsv_profile_map[i].codec_id != codec_id)
            continue;
        if (qsv_profile_map[i].codec_profile == profile)
            return qsv_profile_map[i].mfx_profile;
    }

    return MFX_PROFILE_UNKNOWN;
}