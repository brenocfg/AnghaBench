#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  scale; } ;
typedef  TYPE_1__ PgdRenderDemo ;
typedef  int /*<<< orphan*/  GtkSpinButton ;

/* Variables and functions */
 int /*<<< orphan*/  gtk_spin_button_get_value (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_render_scale_selector_value_changed (GtkSpinButton *spinbutton,
					 PgdRenderDemo *demo)
{
	demo->scale = gtk_spin_button_get_value (spinbutton);
}