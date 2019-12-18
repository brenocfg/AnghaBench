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
typedef  int /*<<< orphan*/  signal_user_data_t ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkLabel ;
typedef  int /*<<< orphan*/  GtkFileChooserButton ;
typedef  int /*<<< orphan*/  GtkEntry ;
typedef  int /*<<< orphan*/  GtkCheckButton ;
typedef  int /*<<< orphan*/  GtkBox ;
typedef  int /*<<< orphan*/  GCallback ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_ALIGN_CENTER ; 
 int /*<<< orphan*/  GTK_ALIGN_FILL ; 
 int /*<<< orphan*/  GTK_ALIGN_START ; 
 int /*<<< orphan*/ * GTK_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GTK_CHECK_BUTTON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GTK_ENTRY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER ; 
 int /*<<< orphan*/ * GTK_FILE_CHOOSER_BUTTON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GTK_LABEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_ORIENTATION_HORIZONTAL ; 
 int /*<<< orphan*/  GTK_ORIENTATION_VERTICAL ; 
 int /*<<< orphan*/ * GTK_WIDGET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  default_title_attrs ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_box_append_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_entry_set_width_chars (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gtk_box_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_box_set_spacing (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gtk_check_button_new () ; 
 int /*<<< orphan*/  gtk_entry_new () ; 
 int /*<<< orphan*/  gtk_file_chooser_button_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_label_get_attributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_label_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_label_set_width_chars (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gtk_widget_set_halign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_has_tooltip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_hexpand (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gtk_widget_set_tooltip_markup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_tooltip_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_valign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 scalar_t__ title_dest_dir_cb ; 
 scalar_t__ title_dest_file_cb ; 
 scalar_t__ title_selected_cb ; 

GtkWidget * title_create_row(signal_user_data_t *ud)
{
    GtkBox *hbox, *vbox_dest;
    GtkCheckButton *selected;
    GtkLabel *title;
    GtkEntry *dest_file;
    GtkFileChooserButton *dest_dir;

    hbox = GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0));
    gtk_box_set_spacing(hbox, 6);
    gtk_widget_show(GTK_WIDGET(hbox));

    // Select checkbox
    selected = GTK_CHECK_BUTTON(gtk_check_button_new());
    gtk_widget_set_tooltip_markup(GTK_WIDGET(selected),
      _("Select this title for adding to the queue.\n"));
    gtk_widget_set_valign(GTK_WIDGET(selected), GTK_ALIGN_CENTER);
    gtk_widget_set_name(GTK_WIDGET(selected), "title_selected");
    gtk_widget_show(GTK_WIDGET(selected));
    g_signal_connect(selected, "toggled", (GCallback)title_selected_cb, ud);
    ghb_box_append_child(hbox, GTK_WIDGET(selected));

    // Title label
    title = GTK_LABEL(gtk_label_new(_("No Title")));
    gtk_label_set_width_chars(title, 12);
    gtk_widget_set_halign(GTK_WIDGET(title), GTK_ALIGN_START);
    gtk_widget_set_valign(GTK_WIDGET(title), GTK_ALIGN_CENTER);
    gtk_widget_set_name(GTK_WIDGET(title), "title_label");
    gtk_widget_show(GTK_WIDGET(title));
    ghb_box_append_child(hbox, GTK_WIDGET(title));

    default_title_attrs = gtk_label_get_attributes(title);
    gtk_widget_set_tooltip_text(GTK_WIDGET(title),
        _("There is another title with the same destination file name.\n"
        "This title will not be added to the queue unless you change\n"
        "the output file name.\n"));
    gtk_widget_set_has_tooltip(GTK_WIDGET(title), FALSE);

    // Destination entry and file chooser
    vbox_dest = GTK_BOX(gtk_box_new(GTK_ORIENTATION_VERTICAL, 0));
    gtk_widget_set_hexpand(GTK_WIDGET(vbox_dest), TRUE);
    gtk_widget_set_halign(GTK_WIDGET(vbox_dest), GTK_ALIGN_FILL);
    //gtk_widget_set_hexpand(GTK_WIDGET(vbox_dest), TRUE);
    dest_file = GTK_ENTRY(gtk_entry_new());
    ghb_entry_set_width_chars(dest_file, 40);
    gtk_widget_set_name(GTK_WIDGET(dest_file), "title_file");
    //gtk_widget_set_hexpand(GTK_WIDGET(dest_file), TRUE);
    gtk_widget_show(GTK_WIDGET(dest_file));
    g_signal_connect(dest_file, "changed", (GCallback)title_dest_file_cb, ud);
    ghb_box_append_child(vbox_dest, GTK_WIDGET(dest_file));
    dest_dir = GTK_FILE_CHOOSER_BUTTON(
            gtk_file_chooser_button_new(_("Destination Directory"),
                                        GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER));
    g_signal_connect(dest_dir, "selection-changed",
                    (GCallback)title_dest_dir_cb, ud);
    gtk_widget_set_name(GTK_WIDGET(dest_dir), "title_dir");
    gtk_widget_set_hexpand(GTK_WIDGET(dest_dir), TRUE);
    gtk_widget_show(GTK_WIDGET(dest_dir));
    ghb_box_append_child(vbox_dest, GTK_WIDGET(dest_dir));
    gtk_widget_show(GTK_WIDGET(vbox_dest));
    ghb_box_append_child(hbox, GTK_WIDGET(vbox_dest));

    return GTK_WIDGET(hbox);
}