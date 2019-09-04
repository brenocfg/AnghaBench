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
typedef  scalar_t__ gint ;
struct TYPE_3__ {scalar_t__ num_page; } ;
typedef  TYPE_1__ PgdAnnotsDemo ;
typedef  int /*<<< orphan*/  GtkSpinButton ;

/* Variables and functions */
 scalar_t__ gtk_spin_button_get_value (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_annots_page_selector_value_changed (GtkSpinButton *spinbutton,
                                        PgdAnnotsDemo *demo)
{
    demo->num_page = (gint) gtk_spin_button_get_value (spinbutton) - 1;
}