#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
struct tm {int dummy; } ;
struct stat {double st_size; } ;
struct TYPE_9__ {int /*<<< orphan*/  builder; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ signal_user_data_t ;
struct TYPE_10__ {int state; int eta_seconds; int paused; int pass_count; int pass_id; int error; int /*<<< orphan*/  pass; } ;
typedef  TYPE_2__ ghb_instance_status_t ;
struct TYPE_11__ {char const* str; } ;
typedef  int /*<<< orphan*/  GtkListBoxRow ;
typedef  int /*<<< orphan*/  GtkListBox ;
typedef  int /*<<< orphan*/  GtkLabel ;
typedef  int /*<<< orphan*/  GhbValue ;
typedef  TYPE_3__ GString ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  GHB_ERROR_CANCELED 134 
#define  GHB_ERROR_FAIL 133 
#define  GHB_ERROR_NONE 132 
 int GHB_STATE_SCANNING ; 
 int GHB_STATE_WORKDONE ; 
 int GHB_STATE_WORKING ; 
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GTK_LABEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GTK_LIST_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ *) ; 
#define  HB_PASS_ENCODE 131 
#define  HB_PASS_ENCODE_1ST 130 
#define  HB_PASS_ENCODE_2ND 129 
#define  HB_PASS_SUBTITLE 128 
 int /*<<< orphan*/  TRUE ; 
 char const* _ (char*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ g_stat (char const*,struct stat*) ; 
 char* g_strdup_printf (char const*,double,...) ; 
 int /*<<< orphan*/  g_string_append_printf (TYPE_3__*,char const*,int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  g_string_free (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* g_string_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ ,int) ; 
 int ghb_array_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_break_duration (int,int*,int*,int*) ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 char* ghb_dict_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gtk_label_set_text (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * gtk_list_box_get_selected_row (int /*<<< orphan*/ *) ; 
 int gtk_list_box_row_get_index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_set_visible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tm* localtime (int*) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 int time (int /*<<< orphan*/ *) ; 

void
ghb_queue_update_live_stats(signal_user_data_t * ud, int index, ghb_instance_status_t * status)
{
    int count = ghb_array_len(ud->queue);
    if (index < 0 || index >= count)
    {
        // invalid index
        return;
    }

    GtkListBox    * lb;
    GtkListBoxRow * row;

    lb = GTK_LIST_BOX(GHB_WIDGET(ud->builder, "queue_list"));
    row = gtk_list_box_get_selected_row(lb);
    if (row == NULL || index != gtk_list_box_row_get_index(row))
    {
        return;
    }

    GhbValue * queueDict, * uiDict;
    queueDict = ghb_array_get(ud->queue, index);
    if (queueDict == NULL) // should never happen
    {
        return;
    }
    uiDict    = ghb_dict_get(queueDict, "uiSettings");
    if (uiDict == NULL) // should never happen
    {
        return;
    }

    GString    * gstr = NULL;
    GtkLabel   * label;
    struct tm  * tm;
    char         date[40] = "";
    char       * str;
    const char * pass = "";
    const char * result = "";
    time_t       start, finish, paused, duration;

    start  = ghb_dict_get_int(uiDict, "job_start_time");
    finish = time(NULL);
    if (status->state & GHB_STATE_WORKING)
    {
        finish += status->eta_seconds;
    }
    paused = status->paused / 1000;
    if ((status->state & GHB_STATE_WORKING) && status->pass_count > 1)
    {
        label = GTK_LABEL(GHB_WIDGET(ud->builder, "queue_stats_pass_label"));
        gtk_widget_set_visible(GTK_WIDGET(label), TRUE);
        label = GTK_LABEL(GHB_WIDGET(ud->builder, "queue_stats_pass"));
        gtk_widget_set_visible(GTK_WIDGET(label), TRUE);
        switch (status->pass_id)
        {
            case HB_PASS_SUBTITLE:
                pass = _("Foreign Audio Search");
                break;

            case HB_PASS_ENCODE:
                pass = _("Encode");
                break;

            case HB_PASS_ENCODE_1ST:
                pass = _("Encode First Pass (Analysis)");
                break;

            case HB_PASS_ENCODE_2ND:
                pass = _("Encode Second Pass (Final)");
                break;

            default:
                // Should never happen
                pass = _("Error");
                break;
        }
        gstr = g_string_new(NULL);
        g_string_append_printf(gstr, _("pass %d of %d\n%s"), status->pass, status->pass_count, pass);
    }
    else
    {
        label = GTK_LABEL(GHB_WIDGET(ud->builder, "queue_stats_pass_label"));
        gtk_widget_set_visible(GTK_WIDGET(label), FALSE);
        label = GTK_LABEL(GHB_WIDGET(ud->builder, "queue_stats_pass"));
        gtk_widget_set_visible(GTK_WIDGET(label), FALSE);
    }

    if (status->state & GHB_STATE_SCANNING)
    {
        result = _("Scanning Title");
    }
    else if (status->state & GHB_STATE_SCANNING)
    {
        result = _("Encoding Paused");
    }
    else if (status->state & GHB_STATE_WORKING)
    {
        result = _("Encoding In Progress");
    }
    else if (status->state & GHB_STATE_WORKDONE)
    {
        switch (status->error)
        {
            case GHB_ERROR_NONE:
                result = _("Completed");
                break;

            case GHB_ERROR_CANCELED:
                result = _("Canceled");
                break;

            case GHB_ERROR_FAIL:
                result = _("Failed");
                break;

            default:
                // Should never happen
                result = _("Unknown");
                break;
        }
    }

    if (gstr != NULL)
    {
        label = GTK_LABEL(GHB_WIDGET(ud->builder, "queue_stats_pass"));
        gtk_label_set_text(label, gstr->str);
        g_string_free(gstr, TRUE);
    }

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