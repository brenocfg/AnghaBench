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
typedef  int /*<<< orphan*/  hb_title_t ;
typedef  int /*<<< orphan*/  hb_job_t ;
typedef  int /*<<< orphan*/  hb_handle_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_error (char*,int) ; 
 int /*<<< orphan*/ * hb_find_title_by_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hb_job_close (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * hb_job_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_job_to_dict (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_preset_apply_filters (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ hb_preset_apply_mux (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ hb_preset_apply_title (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ hb_preset_apply_video (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 

hb_dict_t* hb_preset_job_init(hb_handle_t *h, int title_index,
                              const hb_dict_t *preset)
{
    hb_title_t *title = hb_find_title_by_index(h, title_index);
    if (title == NULL)
    {
        hb_error("Invalid title index (%d)", title_index);
        return NULL;
    }

    hb_job_t *job = hb_job_init(title);
    hb_dict_t *job_dict = hb_job_to_dict(job);
    hb_job_close(&job);

    if (hb_preset_apply_mux(preset, job_dict) < 0)
        goto fail;

    if (hb_preset_apply_video(preset, job_dict) < 0)
        goto fail;

    if (hb_preset_apply_filters(preset, job_dict) < 0)
        goto fail;

    if (hb_preset_apply_title(h, title_index, preset, job_dict) < 0)
        goto fail;

    return job_dict;

fail:
    hb_value_free(&job_dict);
    return NULL;
}