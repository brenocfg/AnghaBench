#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  builder; TYPE_1__* preview; } ;
typedef  TYPE_2__ signal_user_data_t ;
struct TYPE_7__ {int /*<<< orphan*/  pix; int /*<<< orphan*/  scaled_pix; } ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  do_preview_scaling (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_queue_draw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_preview_image (TYPE_2__*) ; 
 int /*<<< orphan*/  set_mini_preview_image (TYPE_2__*,int /*<<< orphan*/ ) ; 

void
ghb_set_preview_image(signal_user_data_t *ud)
{
    init_preview_image(ud);

    // Scale and display the mini-preview
    set_mini_preview_image(ud, ud->preview->pix);

    // Scale the full size preview
    ud->preview->scaled_pix = do_preview_scaling(ud, ud->preview->pix);

    // Display full size preview
    GtkWidget *widget = GHB_WIDGET(ud->builder, "preview_image");
    gtk_widget_queue_draw(widget);
}