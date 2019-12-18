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
struct TYPE_3__ {int /*<<< orphan*/  settings; int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  scalar_t__ gint ;
typedef  scalar_t__ gdouble ;
typedef  char gchar ;
typedef  int gboolean ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GhbValue ;
typedef  int /*<<< orphan*/  GObject ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char const*) ; 
 int TRUE ; 
 int /*<<< orphan*/  g_debug (char*,char const*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_message (char*) ; 
 int /*<<< orphan*/  g_strfreev (char**) ; 
 char** g_strsplit (char const*,char*,int) ; 
 scalar_t__ g_strtod (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ghb_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char const*) ; 
 char* ghb_dict_get_string_xform (int /*<<< orphan*/ ,char const*) ; 
 int ghb_value_get_bool (int /*<<< orphan*/ *) ; 
 char* ghb_value_get_string (int /*<<< orphan*/ *) ; 
 scalar_t__ ghb_widget_double (int /*<<< orphan*/ *) ; 
 char* ghb_widget_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_builder_get_object (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  gtk_widget_is_sensitive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rev_map ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static gboolean
dep_check(signal_user_data_t *ud, const gchar *name, gboolean *out_hide)
{
    GtkWidget *widget;
    GObject *dep_object;
    gint ii;
    gint count;
    gboolean result = TRUE;
    GhbValue *array, *data;
    const gchar *widget_name;

    g_debug("dep_check () %s", name);

    if (rev_map == NULL) return TRUE;
    array = ghb_dict_get(rev_map, name);
    count = ghb_array_len(array);
    *out_hide = FALSE;
    for (ii = 0; ii < count; ii++)
    {
        data = ghb_array_get(array, ii);
        widget_name = ghb_value_get_string(ghb_array_get(data, 0));
        widget = GHB_WIDGET(ud->builder, widget_name);
        dep_object = gtk_builder_get_object(ud->builder, name);
        if (widget != NULL && !gtk_widget_is_sensitive(widget))
        {
            continue;
        }
        if (dep_object == NULL)
        {
            g_message("Failed to find widget");
        }
        else
        {
            gchar *value;
            gint jj = 0;
            gchar **values;
            gboolean sensitive = FALSE;
            gboolean die, hide;

            die = ghb_value_get_bool(ghb_array_get(data, 2));
            hide = ghb_value_get_bool(ghb_array_get(data, 3));
            const char *tmp = ghb_value_get_string(ghb_array_get(data, 1));
            values = g_strsplit(tmp, "|", 10);

            if (widget)
                value = ghb_widget_string(widget);
            else
                value = ghb_dict_get_string_xform(ud->settings, widget_name);
            while (values && values[jj])
            {
                if (values[jj][0] == '>')
                {
                    gdouble dbl = g_strtod (&values[jj][1], NULL);
                    gdouble dvalue = ghb_widget_double(widget);
                    if (dvalue > dbl)
                    {
                        sensitive = TRUE;
                        break;
                    }
                }
                else if (values[jj][0] == '<')
                {
                    gdouble dbl = g_strtod (&values[jj][1], NULL);
                    gdouble dvalue = ghb_widget_double(widget);
                    if (dvalue < dbl)
                    {
                        sensitive = TRUE;
                        break;
                    }
                }
                if (strcmp(values[jj], value) == 0)
                {
                    sensitive = TRUE;
                    break;
                }
                jj++;
            }
            sensitive = die ^ sensitive;
            if (!sensitive)
            {
                result = FALSE;
                *out_hide |= hide;
            }
            g_strfreev (values);
            g_free(value);
        }
    }
    return result;
}