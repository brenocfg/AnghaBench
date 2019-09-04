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
typedef  scalar_t__ gint ;
struct TYPE_4__ {scalar_t__ page; } ;
typedef  TYPE_1__ PgdRenderDemo ;
typedef  int /*<<< orphan*/  GtkSpinButton ;

/* Variables and functions */
 scalar_t__ gtk_spin_button_get_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_render_slice_selector_setup (TYPE_1__*) ; 

__attribute__((used)) static void
pgd_render_page_selector_value_changed (GtkSpinButton *spinbutton,
					PgdRenderDemo *demo)
{
	demo->page = (gint)gtk_spin_button_get_value (spinbutton) - 1;
	pgd_render_slice_selector_setup (demo);
}