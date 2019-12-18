#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  builder; TYPE_1__* preview; } ;
typedef  TYPE_2__ signal_user_data_t ;
typedef  int gint64 ;
typedef  int gdouble ;
struct TYPE_5__ {scalar_t__ state; int len; int pos; int /*<<< orphan*/  play; int /*<<< orphan*/  progress_lock; scalar_t__ seek_lock; int /*<<< orphan*/  live_enabled; } ;
typedef  int /*<<< orphan*/  GtkRange ;
typedef  scalar_t__ GstFormat ;
typedef  int /*<<< orphan*/  GSourceFunc ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ GST_FORMAT_TIME ; 
 int GST_MSECOND ; 
 int /*<<< orphan*/ * GTK_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ PREVIEW_STATE_LIVE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_idle_add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ gst_element_query_duration (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 scalar_t__ gst_element_query_position (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  gtk_range_set_value (int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlock_progress_cb ; 

void
ghb_live_preview_progress(signal_user_data_t *ud)
{
#if defined(_ENABLE_GST)
    GstFormat fmt = GST_FORMAT_TIME;
    gint64 len = -1, pos = -1;

    if (!ud->preview->live_enabled)
        return;

    if (ud->preview->state != PREVIEW_STATE_LIVE || ud->preview->seek_lock)
        return;

    ud->preview->progress_lock = TRUE;
    if (gst_element_query_duration(ud->preview->play, fmt, &len))
    {
        if (len != -1 && fmt == GST_FORMAT_TIME)
        {
            ud->preview->len = len / GST_MSECOND;
        }
    }
    if (gst_element_query_position(ud->preview->play, fmt, &pos))
    {
        if (pos != -1 && fmt == GST_FORMAT_TIME)
        {
            ud->preview->pos = pos / GST_MSECOND;
        }
    }
    if (ud->preview->len > 0)
    {
        GtkRange *progress;
        gdouble percent;

        percent = (gdouble)ud->preview->pos * 100 / ud->preview->len;
        progress = GTK_RANGE(GHB_WIDGET(ud->builder, "live_preview_progress"));
        gtk_range_set_value(progress, percent);
    }
    g_idle_add((GSourceFunc)unlock_progress_cb, ud);
#endif
}