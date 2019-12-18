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
struct TYPE_4__ {int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  GtkTreeView ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_init_lang_list (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ghb_init_lang_list_model (int /*<<< orphan*/ *) ; 

void ghb_init_audio_defaults_ui(signal_user_data_t *ud)
{
    GtkTreeView * tv;

    tv = GTK_TREE_VIEW(GHB_WIDGET(ud->builder, "audio_avail_lang"));
    ghb_init_lang_list(tv, ud);
    tv = GTK_TREE_VIEW(GHB_WIDGET(ud->builder, "audio_selected_lang"));
    ghb_init_lang_list_model(tv);
}