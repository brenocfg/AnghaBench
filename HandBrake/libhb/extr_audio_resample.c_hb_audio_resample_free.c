#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * swresample; } ;
typedef  TYPE_1__ hb_audio_resample_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  swr_free (int /*<<< orphan*/ **) ; 

void hb_audio_resample_free(hb_audio_resample_t *resample)
{
    if (resample != NULL)
    {
        if (resample->swresample != NULL)
        {
            swr_free(&resample->swresample);
        }
        free(resample);
    }
}