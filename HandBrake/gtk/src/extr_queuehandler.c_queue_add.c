#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * queue; int /*<<< orphan*/ * prefs; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GHB_QUEUE_PENDING ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  add_to_queue_list (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_array_new () ; 
 int /*<<< orphan*/ * ghb_dict_new () ; 
 int /*<<< orphan*/  ghb_dict_remove (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_dict_set_int (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_finalize_job (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_get_job_settings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_get_title_settings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_queue_buttons_grey (TYPE_1__*) ; 
 int /*<<< orphan*/  ghb_save_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_update_pending (TYPE_1__*) ; 
 int /*<<< orphan*/ * ghb_value_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  validate_settings (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean
queue_add(signal_user_data_t *ud, GhbValue *settings, gint batch)
{
    // Add settings to the queue
    if (!validate_settings(ud, settings, batch))
    {
        return FALSE;
    }

    if (ud->queue == NULL)
        ud->queue = ghb_array_new();

    ghb_finalize_job(settings);

    GhbValue *titleDict  = ghb_get_title_settings(settings);
    GhbValue *jobDict    = ghb_get_job_settings(settings);
    GhbValue *uiDict     = ghb_value_dup(settings);

    ghb_dict_remove(uiDict, "Job");
    ghb_dict_remove(uiDict, "Title");

    GhbValue *queueDict  = ghb_dict_new();
    ghb_dict_set(queueDict, "uiSettings", uiDict);
    ghb_dict_set(queueDict, "Job", ghb_value_dup(jobDict));
    ghb_dict_set(queueDict, "Title", ghb_value_dup(titleDict));

    // Copy current prefs into settings
    // The job should run with the preferences that existed
    // when the job was added to the queue.
    ghb_dict_set(uiDict, "Preferences", ghb_value_dup(ud->prefs));

    // Make a copy of current settings to be used for the new job
    ghb_dict_set_int(uiDict, "job_status", GHB_QUEUE_PENDING);
    ghb_dict_set_int(uiDict, "job_unique_id", 0);

    ghb_array_append(ud->queue, queueDict);
    add_to_queue_list(ud, queueDict);
    ghb_save_queue(ud->queue);
    ghb_update_pending(ud);
    ghb_queue_buttons_grey(ud);

    return TRUE;
}