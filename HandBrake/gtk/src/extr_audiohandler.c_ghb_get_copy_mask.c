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
typedef  int gint ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int HB_ACODEC_AAC_PASS ; 
 int HB_ACODEC_AC3_PASS ; 
 int HB_ACODEC_DCA_HD_PASS ; 
 int HB_ACODEC_DCA_PASS ; 
 int HB_ACODEC_EAC3_PASS ; 
 int HB_ACODEC_FLAC_PASS ; 
 int HB_ACODEC_MP3_PASS ; 
 int HB_ACODEC_TRUEHD_PASS ; 
 scalar_t__ ghb_dict_get_bool (int /*<<< orphan*/ *,char*) ; 

int ghb_get_copy_mask(GhbValue *settings)
{
    gint mask = 0;

    if (ghb_dict_get_bool(settings, "AudioAllowMP3Pass"))
    {
        mask |= HB_ACODEC_MP3_PASS;
    }
    if (ghb_dict_get_bool(settings, "AudioAllowAACPass"))
    {
        mask |= HB_ACODEC_AAC_PASS;
    }
    if (ghb_dict_get_bool(settings, "AudioAllowAC3Pass"))
    {
        mask |= HB_ACODEC_AC3_PASS;
    }
    if (ghb_dict_get_bool(settings, "AudioAllowDTSPass"))
    {
        mask |= HB_ACODEC_DCA_PASS;
    }
    if (ghb_dict_get_bool(settings, "AudioAllowDTSHDPass"))
    {
        mask |= HB_ACODEC_DCA_HD_PASS;
    }
    if (ghb_dict_get_bool(settings, "AudioAllowEAC3Pass"))
    {
        mask |= HB_ACODEC_EAC3_PASS;
    }
    if (ghb_dict_get_bool(settings, "AudioAllowFLACPass"))
    {
        mask |= HB_ACODEC_FLAC_PASS;
    }
    if (ghb_dict_get_bool(settings, "AudioAllowTRUEHDPass"))
    {
        mask |= HB_ACODEC_TRUEHD_PASS;
    }
    return mask;
}