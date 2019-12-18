#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  gpointer ;
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  gchar ;
typedef  scalar_t__ gboolean ;
struct TYPE_9__ {int /*<<< orphan*/  opts; int /*<<< orphan*/ * name; int /*<<< orphan*/  (* opts_set ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*) ;} ;
typedef  TYPE_2__ combo_name_map_t ;
typedef  int /*<<< orphan*/  GtkComboBox ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * GTK_COMBO_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_TYPE_COMBO_BOX ; 
 int /*<<< orphan*/  G_SIGNAL_MATCH_ID ; 
 TYPE_2__* combo_name_map ; 
 TYPE_2__* find_combo_map (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  g_signal_handler_block (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ g_signal_handler_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_handler_unblock (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ g_signal_lookup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*) ; 

void
ghb_update_ui_combo_box(
    signal_user_data_t *ud,
    const gchar *name,
    const void* user_data,
    gboolean all)
{
    GtkComboBox *combo = NULL;
    gint signal_id;
    gint handler_id = 0;

    if (name != NULL)
    {
        // Clearing a combo box causes a rash of "changed" events, even when
        // the active item is -1 (inactive).  To control things, I'm disabling
        // the event till things are settled down.
        combo = GTK_COMBO_BOX(GHB_WIDGET(ud->builder, name));
        signal_id = g_signal_lookup("changed", GTK_TYPE_COMBO_BOX);
        if (signal_id > 0)
        {
            // Valid signal id found.  This should always succeed.
            handler_id = g_signal_handler_find ((gpointer)combo, G_SIGNAL_MATCH_ID,
                                                signal_id, 0, 0, 0, 0);
            if (handler_id > 0)
            {
                // This should also always succeed
                g_signal_handler_block ((gpointer)combo, handler_id);
            }
        }
    }
    if (all)
    {
        int ii;
        for (ii = 0; combo_name_map[ii].name != NULL; ii++)
        {
            combo_name_map_t *entry = &combo_name_map[ii];
            entry->opts_set(ud, entry->name, entry->opts, user_data);
        }
    }
    else
    {
        combo_name_map_t *entry = find_combo_map(name);
        if (entry != NULL)
        {
            entry->opts_set(ud, entry->name, entry->opts, user_data);
        }
    }
    if (handler_id > 0)
    {
        g_signal_handler_unblock ((gpointer)combo, handler_id);
    }
}