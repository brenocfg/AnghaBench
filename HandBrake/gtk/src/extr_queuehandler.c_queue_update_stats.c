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
typedef  int time_t ;
struct tm {int dummy; } ;
struct stat {double st_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  GtkLabel ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  GHB_QUEUE_CANCELED 132 
#define  GHB_QUEUE_DONE 131 
#define  GHB_QUEUE_FAIL 130 
#define  GHB_QUEUE_PENDING 129 
#define  GHB_QUEUE_RUNNING 128 
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GTK_LABEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ *) ; 
 char const* _ (char*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ g_stat (char const*,struct stat*) ; 
 char* g_strdup_printf (char const*,double,...) ; 
 int /*<<< orphan*/  ghb_break_duration (int,int*,int*,int*) ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 char* ghb_dict_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gtk_label_set_text (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  gtk_widget_set_visible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tm* localtime (int*) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 

void
queue_update_stats(GhbValue * queueDict, signal_user_data_t *ud)
{
    GhbValue * uiDict;
    GtkLabel * label;

    uiDict = ghb_dict_get(queueDict, "uiSettings");
    if (uiDict == NULL) // should never happen
    {
        return;
    }

    label = GTK_LABEL(GHB_WIDGET(ud->builder, "queue_stats_pass_label"));
    gtk_widget_set_visible(GTK_WIDGET(label), FALSE);
    label = GTK_LABEL(GHB_WIDGET(ud->builder, "queue_stats_pass"));
    gtk_widget_set_visible(GTK_WIDGET(label), FALSE);

    const char * result = "";
    int status = ghb_dict_get_int(uiDict, "job_status");

    if (status == GHB_QUEUE_PENDING)
    {
        label = GTK_LABEL(GHB_WIDGET(ud->builder, "queue_stats_start_time"));
        gtk_label_set_text(label, "");
        label = GTK_LABEL(GHB_WIDGET(ud->builder, "queue_stats_finish_time"));
        gtk_label_set_text(label, "");
        label = GTK_LABEL(GHB_WIDGET(ud->builder, "queue_stats_paused"));
        gtk_label_set_text(label, "");
        label = GTK_LABEL(GHB_WIDGET(ud->builder, "queue_stats_encode"));
        gtk_label_set_text(label, "");
        label = GTK_LABEL(GHB_WIDGET(ud->builder, "queue_stats_file_size"));
        gtk_label_set_text(label, "");
        label = GTK_LABEL(GHB_WIDGET(ud->builder, "queue_stats_result"));
        gtk_label_set_text(label, "Pending");
        return;
    }

    switch (status)
    {
        case GHB_QUEUE_RUNNING:
            // This job is running.
            // ghb_queue_update_live_stats() will update stats
            return;

        case GHB_QUEUE_DONE:
            result = _("Completed");
            break;

        case GHB_QUEUE_CANCELED:
            result = _("Canceled");
            break;

        case GHB_QUEUE_FAIL:
            result = _("Failed");
            break;

        case GHB_QUEUE_PENDING:
        default:
            result = _("Pending");
            break;
    }

    struct tm  * tm;
    char         date[40] = "";
    char       * str;
    time_t       start, finish, paused, duration;

    start  = ghb_dict_get_int(uiDict, "job_start_time");
    finish = ghb_dict_get_int(uiDict, "job_finish_time");
    paused = ghb_dict_get_int(uiDict, "job_pause_time_ms") / 1000;

    tm     = localtime( &start );
    strftime(date, 40, "%c", tm);
    label = GTK_LABEL(GHB_WIDGET(ud->builder, "queue_stats_start_time"));
    gtk_label_set_text(label, date);

    tm  = localtime( &finish );
    strftime(date, 40, "%c", tm);
    label = GTK_LABEL(GHB_WIDGET(ud->builder, "queue_stats_finish_time"));
    gtk_label_set_text(label, date);

    int dd = 0, hh, mm, ss;
    ghb_break_duration(paused, &hh, &mm, &ss);
    if (hh >= 24)
    {
        dd = hh / 24;
        hh = hh - dd * 24;
    }
    switch (dd)
    {
        case 0:
            str = g_strdup_printf("%02d:%02d:%02d", hh, mm, ss);
            break;
        case 1:
            str = g_strdup_printf(_("%d Day %02d:%02d:%02d"), dd, hh, mm, ss);
            break;
        default:
            str = g_strdup_printf(_("%d Days %02d:%02d:%02d"), dd, hh, mm, ss);
            break;
    }
    label = GTK_LABEL(GHB_WIDGET(ud->builder, "queue_stats_paused"));
    gtk_label_set_text(label, str);
    g_free(str);

    duration = finish - start;
    if (duration < 0)
    {
        duration = 0;
    }
    dd = 0;
    ghb_break_duration(duration, &hh, &mm, &ss);
    if (hh >= 24)
    {
        dd = hh / 24;
        hh = hh - dd * 24;
    }
    switch (dd)
    {
        case 0:
            str = g_strdup_printf("%02d:%02d:%02d", hh, mm, ss);
            break;
        case 1:
            str = g_strdup_printf(_("%d Day %02d:%02d:%02d"), dd, hh, mm, ss);
            break;
        default:
            str = g_strdup_printf(_("%d Days %02d:%02d:%02d"), dd, hh, mm, ss);
            break;
    }
    label = GTK_LABEL(GHB_WIDGET(ud->builder, "queue_stats_encode"));
    gtk_label_set_text(label, str);
    g_free(str);

    const char  * path;
    struct stat   stbuf;

    path = ghb_dict_get_string(uiDict, "destination");
    if (g_stat(path, &stbuf) == 0)
    {
        const char * units = _("B");
        double size = stbuf.st_size;
        if (size > 1024)
        {
            units = _("KB");
            size /= 1024.0;
        }
        if (size > 1024)
        {
            units = _("MB");
            size /= 1024.0;
        }
        if (size > 1024)
        {
            units = _("GB");
            size /= 1024.0;
        }
        str = g_strdup_printf("%.2f %s", size, units);
        label = GTK_LABEL(GHB_WIDGET(ud->builder, "queue_stats_file_size"));
        gtk_label_set_text(label, str);
        g_free(str);
    }
    else
    {
        label = GTK_LABEL(GHB_WIDGET(ud->builder, "queue_stats_file_size"));
        gtk_label_set_text(label, _("Not Available"));
    }

    label = GTK_LABEL(GHB_WIDGET(ud->builder, "queue_stats_result"));
    gtk_label_set_text(label, result);
}