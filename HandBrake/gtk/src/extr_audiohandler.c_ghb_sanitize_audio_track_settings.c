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
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ *,int) ; 
 int ghb_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_get_job_audio_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_sanitize_audio_settings (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ghb_sanitize_audio_track_settings(GhbValue *settings)
{
    int ii;
    GhbValue *alist = ghb_get_job_audio_list(settings);
    int count = ghb_array_len(alist);

    for (ii = 0; ii < count; ii++)
    {
        GhbValue *asettings = ghb_array_get(alist, ii);
        ghb_sanitize_audio_settings(settings, asettings);
    }
}