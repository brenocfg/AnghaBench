#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
struct TYPE_5__ {int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  char gchar ;
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int GHB_QUEUE_RUNNING ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int ghb_add_job (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ghb_dict_get_bool (int /*<<< orphan*/ *,char*) ; 
 int ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 char* ghb_dict_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_dict_set_int (int /*<<< orphan*/ *,char*,int) ; 
 int ghb_find_queue_job (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_log (char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  ghb_queue_handle () ; 
 int /*<<< orphan*/  ghb_queue_progress_set_visible (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ghb_start_queue () ; 
 int /*<<< orphan*/  start_new_log (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
submit_job(signal_user_data_t *ud, GhbValue *queueDict)
{
    gchar *type, *modified;
    const char *name;
    GhbValue *uiDict;
    gboolean preset_modified;

    g_debug("submit_job");
    if (queueDict == NULL) return;
    uiDict = ghb_dict_get(queueDict, "uiSettings");
    preset_modified = ghb_dict_get_bool(uiDict, "preset_modified");
    name = ghb_dict_get_string(uiDict, "PresetFullName");
    type = ghb_dict_get_int(uiDict, "Type") == 1 ? "Custom " : "";
    modified = preset_modified ? "Modified " : "";
    ghb_log("%s%sPreset: %s", modified, type, name);

    ghb_dict_set_int(uiDict, "job_status", GHB_QUEUE_RUNNING);
    start_new_log(ud, uiDict);
    GhbValue *job_dict = ghb_dict_get(queueDict, "Job");
    int unique_id = ghb_add_job(ghb_queue_handle(), job_dict);
    ghb_dict_set_int(uiDict, "job_unique_id", unique_id);
    time_t now = time(NULL);
    ghb_dict_set_int(uiDict, "job_start_time", now);
    ghb_start_queue();

    // Show queue progress bar
    int index = ghb_find_queue_job(ud->queue, unique_id, NULL);
    ghb_queue_progress_set_visible(ud, index, 1);
}