#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* gint ;
struct TYPE_4__ {void* height; void* width; void* y; void* x; } ;
struct TYPE_5__ {int /*<<< orphan*/  slice_h; TYPE_1__ slice; int /*<<< orphan*/  slice_w; int /*<<< orphan*/  slice_y; int /*<<< orphan*/  slice_x; } ;
typedef  TYPE_2__ PgdRenderDemo ;
typedef  int /*<<< orphan*/  GtkSpinButton ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_SPIN_BUTTON (int /*<<< orphan*/ ) ; 
 scalar_t__ gtk_spin_button_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pgd_render_slice_selector_value_changed (GtkSpinButton *spinbutton,
					 PgdRenderDemo *demo)
{
	demo->slice.x = (gint)gtk_spin_button_get_value (GTK_SPIN_BUTTON (demo->slice_x));
	demo->slice.y = (gint)gtk_spin_button_get_value (GTK_SPIN_BUTTON (demo->slice_y));
	demo->slice.width = (gint)gtk_spin_button_get_value (GTK_SPIN_BUTTON (demo->slice_w));
	demo->slice.height = (gint)gtk_spin_button_get_value (GTK_SPIN_BUTTON (demo->slice_h));
}