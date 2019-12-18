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
 int /*<<< orphan*/ * ghb_create_copy_mask (int /*<<< orphan*/ *) ; 
 int ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_dict_remove (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_get_job_settings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_scan_handle () ; 
 int /*<<< orphan*/  hb_preset_job_add_audio (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ghb_set_pref_audio_settings(GhbValue *settings)
{
    int       title_id;
    GhbValue *copy_mask;

    copy_mask = ghb_create_copy_mask(settings);
    ghb_dict_set(settings, "AudioCopyMask", copy_mask);
    title_id = ghb_dict_get_int(settings, "title");
    GhbValue *job = ghb_get_job_settings(settings);
    ghb_dict_remove(job, "Audio");
    hb_preset_job_add_audio(ghb_scan_handle(), title_id, settings, job);
}