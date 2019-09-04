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
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkDialog ;
typedef  int /*<<< orphan*/  GFile ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_ALIGNMENT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_DIALOG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_ENTRY (int /*<<< orphan*/ *) ; 
 int GTK_EXPAND ; 
 int GTK_FILL ; 
 int /*<<< orphan*/  GTK_ICON_SIZE_DIALOG ; 
 int /*<<< orphan*/  GTK_LABEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_MISC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_RESPONSE_CANCEL ; 
 int /*<<< orphan*/  GTK_RESPONSE_OK ; 
 int /*<<< orphan*/  GTK_STOCK_CANCEL ; 
 int /*<<< orphan*/  GTK_STOCK_DIALOG_AUTHENTICATION ; 
 int /*<<< orphan*/  GTK_TABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * g_file_get_basename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_markup_printf_escaped (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,char*,char*) ; 
 int /*<<< orphan*/ * gtk_alignment_new (double,double,double,double) ; 
 int /*<<< orphan*/  gtk_alignment_set_padding (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_box_set_spacing (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_container_set_border_width (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_dialog_add_buttons (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_dialog_get_action_area (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_dialog_get_content_area (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_dialog_new () ; 
 int /*<<< orphan*/  gtk_dialog_set_alternative_button_order (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_dialog_set_default_response (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_dialog_set_has_separator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_dialog_set_response_sensitive (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_entry_new () ; 
 int /*<<< orphan*/  gtk_entry_set_visibility (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_hbox_new (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gtk_image_new_from_stock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_label_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_label_new_with_mnemonic (char*) ; 
 int /*<<< orphan*/  gtk_label_set_line_wrap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_label_set_markup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_label_set_mnemonic_widget (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_misc_set_alignment (int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  gtk_table_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_table_attach_defaults (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gtk_table_new (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_table_set_col_spacings (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_table_set_row_spacings (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gtk_vbox_new (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_window_set_icon_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_set_modal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_set_resizable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_set_title (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pgd_demo_auth_dialog_entry_activated ; 
 int /*<<< orphan*/  pgd_demo_auth_dialog_entry_changed ; 

__attribute__((used)) static GtkDialog *
pgd_demo_get_auth_dialog (GFile *uri_file)
{
	GtkDialog *dialog;
	GtkWidget *content_area, *action_area;
	GtkWidget *entry_container;
	GtkWidget *password_entry;
	GtkWidget *hbox, *main_vbox, *vbox, *icon;
	GtkWidget *table;
	GtkWidget *label;
	gchar     *format, *markup, *file_name;

	dialog = GTK_DIALOG (gtk_dialog_new ());
	content_area = gtk_dialog_get_content_area (dialog);
	action_area = gtk_dialog_get_action_area (dialog);

	/* Set the dialog up with HIG properties */
	gtk_dialog_set_has_separator (dialog, FALSE);
	gtk_container_set_border_width (GTK_CONTAINER (dialog), 5);
	gtk_box_set_spacing (GTK_BOX (content_area), 2); /* 2 * 5 + 2 = 12 */
	gtk_container_set_border_width (GTK_CONTAINER (action_area), 5);
	gtk_box_set_spacing (GTK_BOX (action_area), 6);

	gtk_window_set_title (GTK_WINDOW (dialog), "Enter password");
	gtk_window_set_resizable (GTK_WINDOW (dialog), FALSE);
	gtk_window_set_icon_name (GTK_WINDOW (dialog), GTK_STOCK_DIALOG_AUTHENTICATION);
	gtk_window_set_modal (GTK_WINDOW (dialog), TRUE);

	gtk_dialog_add_buttons (dialog,
				GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				"_Unlock Document", GTK_RESPONSE_OK,
				NULL);
	gtk_dialog_set_default_response (dialog, GTK_RESPONSE_OK);
	gtk_dialog_set_response_sensitive (GTK_DIALOG (dialog),
					   GTK_RESPONSE_OK, FALSE);
	gtk_dialog_set_alternative_button_order (dialog,
						 GTK_RESPONSE_OK,
						 GTK_RESPONSE_CANCEL,
						 -1);

	/* Build contents */
	hbox = gtk_hbox_new (FALSE, 12);
	gtk_container_set_border_width (GTK_CONTAINER (hbox), 5);
	gtk_box_pack_start (GTK_BOX (content_area), hbox, TRUE, TRUE, 0);
	gtk_widget_show (hbox);

	icon = gtk_image_new_from_stock (GTK_STOCK_DIALOG_AUTHENTICATION,
					 GTK_ICON_SIZE_DIALOG);

	gtk_misc_set_alignment (GTK_MISC (icon), 0.5, 0.0);
	gtk_box_pack_start (GTK_BOX (hbox), icon, FALSE, FALSE, 0);
	gtk_widget_show (icon);

	main_vbox = gtk_vbox_new (FALSE, 18);
	gtk_box_pack_start (GTK_BOX (hbox), main_vbox, TRUE, TRUE, 0);
	gtk_widget_show (main_vbox);

	label = gtk_label_new (NULL);
	gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);
	gtk_label_set_line_wrap (GTK_LABEL (label), TRUE);
	file_name = g_file_get_basename (uri_file);
	format = g_strdup_printf ("<span size=\"larger\" weight=\"bold\">%s</span>\n\n%s",
				  "Password required",
				  "The document “%s” is locked and requires a password before it can be opened.");
	markup = g_markup_printf_escaped (format, file_name);
	gtk_label_set_markup (GTK_LABEL (label), markup);
	g_free (format);
	g_free (markup);
	g_free (file_name);
	gtk_box_pack_start (GTK_BOX (main_vbox), label,
			    FALSE, FALSE, 0);
	gtk_widget_show (label);

	vbox = gtk_vbox_new (FALSE, 6);
	gtk_box_pack_start (GTK_BOX (main_vbox), vbox, FALSE, FALSE, 0);
	gtk_widget_show (vbox);

	/* The table that holds the entries */
	entry_container = gtk_alignment_new (0.0, 0.0, 1.0, 1.0);

	gtk_alignment_set_padding (GTK_ALIGNMENT (entry_container),
				   0, 0, 0, 0);

	gtk_box_pack_start (GTK_BOX (vbox), entry_container,
			    FALSE, FALSE, 0);
	gtk_widget_show (entry_container);

	table = gtk_table_new (1, 2, FALSE);
	gtk_table_set_col_spacings (GTK_TABLE (table), 12);
	gtk_table_set_row_spacings (GTK_TABLE (table), 6);
	gtk_container_add (GTK_CONTAINER (entry_container), table);
	gtk_widget_show (table);

	label = gtk_label_new_with_mnemonic ("_Password:");
	gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);

	password_entry = gtk_entry_new ();
	gtk_entry_set_visibility (GTK_ENTRY (password_entry), FALSE);
	g_signal_connect (password_entry, "changed",
			  G_CALLBACK (pgd_demo_auth_dialog_entry_changed),
			  dialog);
	g_signal_connect (password_entry, "activate",
			  G_CALLBACK (pgd_demo_auth_dialog_entry_activated),
			  dialog);

	gtk_table_attach (GTK_TABLE (table), label,
			  0, 1, 0, 1,
			  GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);
	gtk_widget_show (label);

	gtk_table_attach_defaults (GTK_TABLE (table), password_entry,
				   1, 2, 0, 1);
	gtk_widget_show (password_entry);

	gtk_label_set_mnemonic_widget (GTK_LABEL (label), password_entry);

	return dialog;
}