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
typedef  int /*<<< orphan*/  CustomCellRendererButton ;

/* Variables and functions */
 int GTK_CELL_RENDERER_MODE_ACTIVATABLE ; 
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
custom_cell_renderer_button_init (CustomCellRendererButton *cellbutton)
{
    g_object_set(cellbutton, "mode", GTK_CELL_RENDERER_MODE_ACTIVATABLE, NULL);
    g_object_set(cellbutton, "xpad", 2, NULL);
    g_object_set(cellbutton, "ypad", 2, NULL);
}