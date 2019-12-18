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
typedef  int gint ;
typedef  scalar_t__ gdouble ;
typedef  scalar_t__ gchar ;
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkTextBuffer ;
typedef  scalar_t__ GtkFileChooserAction ;
typedef  int /*<<< orphan*/  GtkEntry ;
typedef  int /*<<< orphan*/  GhbValue ;
typedef  scalar_t__ GType ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ GHB_ARRAY ; 
 scalar_t__ GHB_DICT ; 
 int /*<<< orphan*/  GTK_BIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_CHECK_MENU_ITEM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_COMBO_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_ENTRY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_FILE_CHOOSER (int /*<<< orphan*/ *) ; 
 scalar_t__ GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER ; 
 scalar_t__ GTK_FILE_CHOOSER_ACTION_SAVE ; 
 scalar_t__ GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER ; 
 int /*<<< orphan*/  GTK_LABEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_RANGE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_SCALE_BUTTON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_SPIN_BUTTON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TEXT_VIEW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TOGGLE_BUTTON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TOGGLE_TOOL_BUTTON (int /*<<< orphan*/ *) ; 
 scalar_t__ GTK_TYPE_CHECK_BUTTON ; 
 scalar_t__ GTK_TYPE_CHECK_MENU_ITEM ; 
 scalar_t__ GTK_TYPE_COMBO_BOX ; 
 scalar_t__ GTK_TYPE_ENTRY ; 
 scalar_t__ GTK_TYPE_FILE_CHOOSER_BUTTON ; 
 scalar_t__ GTK_TYPE_LABEL ; 
 scalar_t__ GTK_TYPE_RADIO_BUTTON ; 
 scalar_t__ GTK_TYPE_SCALE ; 
 scalar_t__ GTK_TYPE_SCALE_BUTTON ; 
 scalar_t__ GTK_TYPE_SPIN_BUTTON ; 
 scalar_t__ GTK_TYPE_TEXT_VIEW ; 
 scalar_t__ GTK_TYPE_TOGGLE_BUTTON ; 
 scalar_t__ GTK_TYPE_TOGGLE_TOOL_BUTTON ; 
 int /*<<< orphan*/  G_FILE_TEST_EXISTS ; 
 int /*<<< orphan*/  G_FILE_TEST_IS_DIR ; 
 scalar_t__ G_OBJECT_TYPE (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 scalar_t__ g_file_test (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (scalar_t__*) ; 
 scalar_t__* g_path_get_dirname (scalar_t__*) ; 
 int /*<<< orphan*/  g_warning (char*,char const*) ; 
 int /*<<< orphan*/  ghb_editable_set_text (int /*<<< orphan*/ *,scalar_t__*) ; 
 char* ghb_get_setting_key (int /*<<< orphan*/ *) ; 
 scalar_t__ ghb_value_get_double (int /*<<< orphan*/  const*) ; 
 int ghb_value_get_int (int /*<<< orphan*/  const*) ; 
 scalar_t__* ghb_value_get_string_xform (int /*<<< orphan*/  const*) ; 
 scalar_t__ ghb_value_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  gtk_bin_get_child (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_check_menu_item_set_active (int /*<<< orphan*/ ,int) ; 
 scalar_t__ gtk_combo_box_get_has_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_combo_box_get_model (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_combo_box_set_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_combo_box_set_active_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_file_chooser_get_action (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_file_chooser_set_current_folder (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  gtk_file_chooser_set_filename (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  gtk_file_chooser_unselect_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_label_set_markup (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  gtk_range_set_value (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gtk_scale_button_set_value (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gtk_spin_button_set_value (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gtk_text_buffer_set_text (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/ * gtk_text_view_get_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_toggle_button_set_active (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_toggle_tool_button_set_active (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,...) ; 
 scalar_t__ gtk_tree_model_get_iter_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_tree_model_iter_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (scalar_t__*,scalar_t__*) ; 

void
ghb_update_widget(GtkWidget *widget, const GhbValue *value)
{
    GType type;
    gchar *str, *tmp;
    gint ival;
    gdouble dval;

    const char *name = ghb_get_setting_key(widget);
    type = ghb_value_type(value);
    if (type == GHB_ARRAY || type == GHB_DICT)
        return;
    if (value == NULL) return;
    str = tmp = ghb_value_get_string_xform(value);
    ival = ghb_value_get_int(value);
    dval = ghb_value_get_double(value);
    type = G_OBJECT_TYPE(widget);

    if (str == NULL)
        str = "";

    if (type == GTK_TYPE_ENTRY)
    {
        ghb_editable_set_text(widget, str);
    }
    else if (type == GTK_TYPE_RADIO_BUTTON)
    {
        if (ival)
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), !!ival);
    }
    else if (type == GTK_TYPE_CHECK_BUTTON)
    {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), ival);
    }
    else if (type == GTK_TYPE_TOGGLE_TOOL_BUTTON)
    {
        gtk_toggle_tool_button_set_active(GTK_TOGGLE_TOOL_BUTTON(widget), ival);
    }
    else if (type == GTK_TYPE_TOGGLE_BUTTON)
    {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), ival);
    }
    else if (type == GTK_TYPE_CHECK_MENU_ITEM)
    {
        gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(widget), ival);
    }
    else if (type == GTK_TYPE_COMBO_BOX)
    {
        GtkTreeModel *store;
        GtkTreeIter iter;
        gchar *shortOpt;
        gdouble ivalue;
        gboolean foundit = FALSE;

        store = gtk_combo_box_get_model(GTK_COMBO_BOX(widget));
        if (gtk_tree_model_get_iter_first (store, &iter))
        {
            do
            {
                gtk_tree_model_get(store, &iter, 2, &shortOpt, -1);
                if (strcasecmp(shortOpt, str) == 0)
                {
                    gtk_combo_box_set_active_iter (
                        GTK_COMBO_BOX(widget), &iter);
                    g_free(shortOpt);
                    foundit = TRUE;
                    break;
                }
                g_free(shortOpt);
            } while (gtk_tree_model_iter_next (store, &iter));
        }
        if (!foundit && gtk_tree_model_get_iter_first (store, &iter))
        {
            do
            {
                gtk_tree_model_get(store, &iter, 3, &ivalue, -1);
                if ((gint)ivalue == ival || ivalue == dval)
                {
                    gtk_combo_box_set_active_iter (
                        GTK_COMBO_BOX(widget), &iter);
                    foundit = TRUE;
                    break;
                }
            } while (gtk_tree_model_iter_next (store, &iter));
        }
        if (!foundit)
        {
            if (gtk_combo_box_get_has_entry(GTK_COMBO_BOX(widget)))
            {
                GtkEntry *entry = GTK_ENTRY(gtk_bin_get_child(GTK_BIN(widget)));
                if (entry)
                {
                    ghb_editable_set_text(entry, str);
                }
                else
                {
                    gtk_combo_box_set_active (GTK_COMBO_BOX(widget), 0);
                }
            }
            else
            {
                gtk_combo_box_set_active (GTK_COMBO_BOX(widget), 0);
            }
        }
    }
    else if (type == GTK_TYPE_SPIN_BUTTON)
    {
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), dval);
    }
    else if (type == GTK_TYPE_SCALE)
    {
        gtk_range_set_value(GTK_RANGE(widget), dval);
    }
    else if (type == GTK_TYPE_SCALE_BUTTON)
    {
        gtk_scale_button_set_value(GTK_SCALE_BUTTON(widget), dval);
    }
    else if (type == GTK_TYPE_TEXT_VIEW)
    {
        static int text_view_busy = 0;
        GtkTextBuffer *buffer = gtk_text_view_get_buffer(
                                                GTK_TEXT_VIEW(widget));
        if (!text_view_busy)
        {
            text_view_busy = 1;
            gtk_text_buffer_set_text (buffer, str, -1);
            text_view_busy = 0;
        }
    }
    else if (type == GTK_TYPE_LABEL)
    {
        gtk_label_set_markup (GTK_LABEL(widget), str);
    }
    else if (type == GTK_TYPE_FILE_CHOOSER_BUTTON)
    {
        GtkFileChooserAction act;
        act = gtk_file_chooser_get_action(GTK_FILE_CHOOSER(widget));

        if (str[0] == 0)
        {
            // Do nothing
            ;
        }
        else if (act == GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER ||
                 act == GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER)
        {
            gtk_file_chooser_set_filename (GTK_FILE_CHOOSER(widget), str);
        }
        else if (act == GTK_FILE_CHOOSER_ACTION_SAVE)
        {
            gtk_file_chooser_set_filename (GTK_FILE_CHOOSER(widget), str);
        }
        else
        {
            if (g_file_test(str, G_FILE_TEST_IS_DIR))
            {
                gtk_file_chooser_set_current_folder(
                    GTK_FILE_CHOOSER(widget), str);
            }
            else if (g_file_test(str, G_FILE_TEST_EXISTS))
            {
                gtk_file_chooser_set_filename (GTK_FILE_CHOOSER(widget), str);
            }
            else
            {
                gchar * dirname;

                dirname = g_path_get_dirname(str);
                gtk_file_chooser_set_current_folder(
                    GTK_FILE_CHOOSER(widget), dirname);
                gtk_file_chooser_unselect_all(GTK_FILE_CHOOSER(widget));
                g_free(dirname);
            }
        }
    }
    else
    {
        g_warning("Attempt to set unknown widget type, name %s", name);
    }
    g_free(tmp);
}