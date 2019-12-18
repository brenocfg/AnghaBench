#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  GtkCellRenderer ;

/* Variables and functions */
 int /*<<< orphan*/  CUSTOM_TYPE_CELL_RENDERER_BUTTON ; 
 int /*<<< orphan*/ * g_object_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

GtkCellRenderer *
custom_cell_renderer_button_new (void)
{
    return g_object_new(CUSTOM_TYPE_CELL_RENDERER_BUTTON, NULL);
}