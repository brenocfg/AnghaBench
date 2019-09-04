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
struct TYPE_5__ {scalar_t__ idle_id; scalar_t__ page_index; int /*<<< orphan*/  model; } ;
typedef  TYPE_1__ PgdFindDemo ;
typedef  int /*<<< orphan*/  GtkButton ;
typedef  int /*<<< orphan*/  GSourceFunc ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TREE_STORE (int /*<<< orphan*/ ) ; 
 scalar_t__ g_idle_add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  g_source_remove (scalar_t__) ; 
 int /*<<< orphan*/  gtk_tree_store_clear (int /*<<< orphan*/ ) ; 
 scalar_t__ pgd_find_find_text ; 
 int /*<<< orphan*/  pgd_find_update_progress (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void
pgd_find_button_clicked (GtkButton   *button,
			 PgdFindDemo *demo)
{
	gtk_tree_store_clear (GTK_TREE_STORE (demo->model));
	demo->page_index = 0;
	pgd_find_update_progress (demo, demo->page_index);
	if (demo->idle_id > 0)
		g_source_remove (demo->idle_id);
	demo->idle_id = g_idle_add ((GSourceFunc)pgd_find_find_text, demo);
}