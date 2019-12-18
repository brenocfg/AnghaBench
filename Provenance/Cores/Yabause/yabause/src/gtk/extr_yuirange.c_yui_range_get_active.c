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
typedef  int /*<<< orphan*/  gint ;
struct TYPE_3__ {int /*<<< orphan*/  combo; } ;
typedef  TYPE_1__ YuiRange ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_COMBO_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_combo_box_get_active (int /*<<< orphan*/ ) ; 

gint yui_range_get_active(YuiRange * range) {
	return gtk_combo_box_get_active(GTK_COMBO_BOX(range->combo));
}