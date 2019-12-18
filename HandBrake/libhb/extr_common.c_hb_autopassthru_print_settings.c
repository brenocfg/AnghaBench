#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int acodec_copy_mask; int acodec_fallback; } ;
typedef  TYPE_1__ hb_job_t ;
struct TYPE_7__ {int codec; char* name; } ;
typedef  TYPE_2__ hb_encoder_t ;

/* Variables and functions */
 int HB_ACODEC_AUTO_PASS ; 
 int HB_ACODEC_PASS_FLAG ; 
 int HB_ACODEC_PASS_MASK ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__* hb_audio_encoder_get_next (TYPE_2__ const*) ; 
 int /*<<< orphan*/  hb_log (char*,...) ; 
 char* hb_strncat_dup (char*,char*,int) ; 
 int strlen (char*) ; 

void hb_autopassthru_print_settings(hb_job_t *job)
{
    char *mask = NULL, *tmp;
    const char *fallback = NULL;
    const hb_encoder_t *audio_encoder = NULL;
    while ((audio_encoder = hb_audio_encoder_get_next(audio_encoder)) != NULL)
    {
        if ((audio_encoder->codec &  HB_ACODEC_PASS_FLAG) &&
            (audio_encoder->codec != HB_ACODEC_AUTO_PASS) &&
            (audio_encoder->codec & (job->acodec_copy_mask &
                                     HB_ACODEC_PASS_MASK)))
        {
            if (mask != NULL)
            {
                tmp = hb_strncat_dup(mask, ", ", 2);
                if (tmp != NULL)
                {
                    free(mask);
                    mask = tmp;
                }
            }
            // passthru name without " Passthru"
            tmp = hb_strncat_dup(mask,  audio_encoder->name,
                                 strlen(audio_encoder->name) - 9);
            if (tmp != NULL)
            {
                free(mask);
                mask = tmp;
            }
        }
        else if ((audio_encoder->codec & HB_ACODEC_PASS_FLAG) == 0 &&
                 (audio_encoder->codec == job->acodec_fallback))
        {
            fallback = audio_encoder->name;
        }
    }
    if (mask == NULL)
        hb_log("Auto Passthru: no codecs allowed");
    else
        hb_log("Auto Passthru: allowed codecs are %s", mask);
    if (fallback == NULL)
        hb_log("Auto Passthru: no valid fallback specified");
    else
        hb_log("Auto Passthru: fallback is %s", fallback);
}