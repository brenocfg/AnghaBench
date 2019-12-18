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
typedef  int /*<<< orphan*/  signal_user_data_t ;
struct TYPE_4__ {char* member_0; char* member_2; char* member_3; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_4; } ;
typedef  int /*<<< orphan*/  GApplication ;
typedef  TYPE_1__ GActionEntry ;

/* Variables and functions */
 int /*<<< orphan*/  G_ACTION_MAP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_N_ELEMENTS (TYPE_1__ const*) ; 
 int /*<<< orphan*/ * about_action_cb ; 
 int /*<<< orphan*/ * destination_action_cb ; 
 int /*<<< orphan*/  g_action_map_add_action_entries (int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * guide_action_cb ; 
 int /*<<< orphan*/  hbfd_action_cb ; 
 int /*<<< orphan*/ * preferences_action_cb ; 
 int /*<<< orphan*/ * preset_default_action_cb ; 
 int /*<<< orphan*/ * preset_export_action_cb ; 
 int /*<<< orphan*/ * preset_import_action_cb ; 
 int /*<<< orphan*/ * preset_reload_action_cb ; 
 int /*<<< orphan*/ * preset_remove_action_cb ; 
 int /*<<< orphan*/ * preset_rename_action_cb ; 
 int /*<<< orphan*/ * preset_save_action_cb ; 
 int /*<<< orphan*/ * preset_save_as_action_cb ; 
 int /*<<< orphan*/ * preset_select_action_cb ; 
 int /*<<< orphan*/ * presets_reload_action_cb ; 
 int /*<<< orphan*/ * queue_add_action_cb ; 
 int /*<<< orphan*/ * queue_add_all_action_cb ; 
 int /*<<< orphan*/ * queue_delete_all_action_cb ; 
 int /*<<< orphan*/ * queue_delete_complete_action_cb ; 
 int /*<<< orphan*/ * queue_edit_action_cb ; 
 int /*<<< orphan*/ * queue_export_action_cb ; 
 int /*<<< orphan*/ * queue_import_action_cb ; 
 int /*<<< orphan*/ * queue_open_dest_action_cb ; 
 int /*<<< orphan*/ * queue_open_log_action_cb ; 
 int /*<<< orphan*/ * queue_open_log_dir_action_cb ; 
 int /*<<< orphan*/ * queue_open_source_action_cb ; 
 int /*<<< orphan*/ * queue_pause_action_cb ; 
 int /*<<< orphan*/ * queue_reset_action_cb ; 
 int /*<<< orphan*/ * queue_reset_all_action_cb ; 
 int /*<<< orphan*/ * queue_reset_fail_action_cb ; 
 int /*<<< orphan*/ * queue_start_action_cb ; 
 int /*<<< orphan*/ * quit_action_cb ; 
 int /*<<< orphan*/  show_activity_action_cb ; 
 int /*<<< orphan*/  show_presets_action_cb ; 
 int /*<<< orphan*/  show_preview_action_cb ; 
 int /*<<< orphan*/  show_queue_action_cb ; 
 int /*<<< orphan*/ * single_title_action_cb ; 
 int /*<<< orphan*/ * source_action_cb ; 

__attribute__((used)) static void map_actions(GApplication * app, signal_user_data_t * ud)
{
    const GActionEntry entries[] =
    {
        { "source",                source_action_cb                },
        { "single",                single_title_action_cb          },
        { "destination",           destination_action_cb           },
        { "preferences",           preferences_action_cb           },
        { "quit",                  quit_action_cb                  },
        { "queue-add",             queue_add_action_cb             },
        { "queue-add-all",         queue_add_all_action_cb         },
        { "queue-start",           queue_start_action_cb           },
        { "queue-pause",           queue_pause_action_cb           },
        { "queue-open-source",     queue_open_source_action_cb     },
        { "queue-open-dest",       queue_open_dest_action_cb       },
        { "queue-open-log-dir",    queue_open_log_dir_action_cb    },
        { "queue-open-log",        queue_open_log_action_cb        },
        { "queue-reset-fail",      queue_reset_fail_action_cb      },
        { "queue-reset-all",       queue_reset_all_action_cb       },
        { "queue-reset",           queue_reset_action_cb           },
        { "queue-delete-complete", queue_delete_complete_action_cb },
        { "queue-delete-all",      queue_delete_all_action_cb      },
        { "queue-export",          queue_export_action_cb          },
        { "queue-import",          queue_import_action_cb          },
        { "queue-edit",            queue_edit_action_cb            },
        { "hbfd",                  NULL,
          NULL, "false",           hbfd_action_cb                  },
        { "show-presets",          NULL,
          NULL, "false",           show_presets_action_cb          },
        { "show-queue",            NULL,
          NULL, "false",           show_queue_action_cb            },
        { "show-preview",          NULL,
          NULL, "false",           show_preview_action_cb          },
        { "show-activity",         NULL,
          NULL, "false",           show_activity_action_cb         },
        { "preset-save",           preset_save_action_cb           },
        { "preset-save-as",        preset_save_as_action_cb        },
        { "preset-rename",         preset_rename_action_cb         },
        { "preset-remove",         preset_remove_action_cb         },
        { "preset-default",        preset_default_action_cb        },
        { "preset-export",         preset_export_action_cb         },
        { "preset-import",         preset_import_action_cb         },
        { "presets-reload",        presets_reload_action_cb        },
        { "about",                 about_action_cb                 },
        { "guide",                 guide_action_cb                 },
        { "preset-select",         preset_select_action_cb, "s"    },
        { "preset-reload",         preset_reload_action_cb,        },
    };
    g_action_map_add_action_entries(G_ACTION_MAP(app), entries,
                                    G_N_ELEMENTS(entries), ud);
}