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
struct TYPE_5__ {int /*<<< orphan*/  builder; TYPE_1__* preview; } ;
typedef  TYPE_2__ signal_user_data_t ;
struct TYPE_4__ {int /*<<< orphan*/  state; int /*<<< orphan*/  pause; int /*<<< orphan*/  play; int /*<<< orphan*/  live_enabled; } ;
typedef  int /*<<< orphan*/  GtkRange ;
typedef  int /*<<< orphan*/  GtkImage ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_ICON_SIZE_BUTTON ; 
 int /*<<< orphan*/  GHB_PLAY_ICON ; 
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GST_STATE_NULL ; 
 int /*<<< orphan*/ * GTK_IMAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GTK_RANGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREVIEW_STATE_IMAGE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ghb_image_set_from_icon_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gst_element_set_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_range_set_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
live_preview_stop(signal_user_data_t *ud)
{
    GtkImage *img;
    GtkRange *progress;

    if (!ud->preview->live_enabled)
        return;

    img = GTK_IMAGE(GHB_WIDGET(ud->builder, "live_preview_play_image"));
    ghb_image_set_from_icon_name(img, GHB_PLAY_ICON, GHB_ICON_SIZE_BUTTON);
#if defined(_ENABLE_GST)
    gst_element_set_state(ud->preview->play, GST_STATE_NULL);
#endif
    ud->preview->pause = TRUE;
    ud->preview->state = PREVIEW_STATE_IMAGE;

    progress = GTK_RANGE(GHB_WIDGET(ud->builder, "live_preview_progress"));
    gtk_range_set_value(progress, 0);
}