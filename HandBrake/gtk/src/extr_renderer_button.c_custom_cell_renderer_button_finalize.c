#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* finalize ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  GObject ;

/* Variables and functions */
 TYPE_1__* G_OBJECT_CLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parent_class ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
custom_cell_renderer_button_finalize (GObject *object)
{
    /*
    If you need to do anything with the renderer button ...
    CustomCellRendererProgress *cellrendererbutton = CUSTOM_CELL_RENDERER_BUTTON(object);
    */

    /* Free any dynamically allocated resources here */

    (* G_OBJECT_CLASS (parent_class)->finalize) (object);
}