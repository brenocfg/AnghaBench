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
typedef  float gdouble ;
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkScaleButton ;
typedef  int /*<<< orphan*/  GtkAdjustment ;

/* Variables and functions */
 int /*<<< orphan*/ * GTK_SCALE_BUTTON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_adjustment_configure (int /*<<< orphan*/ *,float,float,float,float,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_scale_button_get_adjustment (int /*<<< orphan*/ *) ; 
 float hb_audio_quality_get_default (int) ; 
 int /*<<< orphan*/  hb_audio_quality_get_limits (int,float*,float*,float*,int*) ; 

__attribute__((used)) static void audio_quality_update_limits(
    GtkWidget *widget,
    int encoder,
    gboolean set_default,
    gdouble value)
{
    float low, high, gran;
    int dir;

    hb_audio_quality_get_limits(encoder, &low, &high, &gran, &dir);
    if (set_default)
    {
        value = hb_audio_quality_get_default(encoder);
    }
    if (dir)
    {
        // Quality values are inverted
        value = high - value + low;
    }
    GtkScaleButton *sb;
    GtkAdjustment *adj;
    sb = GTK_SCALE_BUTTON(widget);
    adj = gtk_scale_button_get_adjustment(sb);
    gtk_adjustment_configure (adj, value, low, high, gran, gran, 0);
}