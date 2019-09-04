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
typedef  int /*<<< orphan*/  gint ;
typedef  char gchar ;
struct TYPE_3__ {char* value_name; } ;
typedef  int /*<<< orphan*/  PopplerFormField ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  TYPE_1__ GEnumValue ;
typedef  int /*<<< orphan*/  GEnumClass ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_ALIGNMENT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_BIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TABLE (int /*<<< orphan*/ *) ; 
#define  POPPLER_FORM_FIELD_BUTTON 132 
#define  POPPLER_FORM_FIELD_CHOICE 131 
#define  POPPLER_FORM_FIELD_SIGNATURE 130 
#define  POPPLER_FORM_FIELD_TEXT 129 
#define  POPPLER_FORM_FIELD_UNKNOWN 128 
 int /*<<< orphan*/  POPPLER_TYPE_FORM_BUTTON_TYPE ; 
 int /*<<< orphan*/  POPPLER_TYPE_FORM_CHOICE_TYPE ; 
 int /*<<< orphan*/  POPPLER_TYPE_FORM_TEXT_TYPE ; 
 int /*<<< orphan*/  g_assert_not_reached () ; 
 TYPE_1__* g_enum_get_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup_printf (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ g_type_class_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_alignment_new (double,double,int,int) ; 
 int /*<<< orphan*/  gtk_alignment_set_padding (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/ * gtk_bin_get_child (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_container_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_table_new (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_table_set_col_spacings (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_table_set_row_spacings (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_form_field_view_add_choice_items (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_table_add_property (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_form_field_button_get_button_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_form_field_button_get_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_form_field_choice_can_select_multiple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_form_field_choice_commit_on_change (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_form_field_choice_do_spell_check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_form_field_choice_get_choice_type (int /*<<< orphan*/ *) ; 
 char* poppler_form_field_choice_get_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poppler_form_field_choice_get_n_items (int /*<<< orphan*/ *) ; 
 char* poppler_form_field_choice_get_text (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_form_field_choice_is_editable (int /*<<< orphan*/ *) ; 
 int poppler_form_field_get_field_type (int /*<<< orphan*/ *) ; 
 char* poppler_form_field_get_mapping_name (int /*<<< orphan*/ *) ; 
 char* poppler_form_field_get_name (int /*<<< orphan*/ *) ; 
 char* poppler_form_field_get_partial_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_form_field_text_do_scroll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_form_field_text_do_spell_check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_form_field_text_get_max_len (int /*<<< orphan*/ *) ; 
 char* poppler_form_field_text_get_text (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_form_field_text_get_text_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_form_field_text_is_password (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_form_field_text_is_rich_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_form_field_view_set_field (GtkWidget        *field_view,
			       PopplerFormField *field)
{
	GtkWidget  *alignment;
	GtkWidget  *table;
	GEnumValue *enum_value;
	gchar      *text;
	gint        row = 0;

	alignment = gtk_bin_get_child (GTK_BIN (field_view));
	if (alignment) {
		gtk_container_remove (GTK_CONTAINER (field_view), alignment);
	}
	
	alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 5, 5, 12, 5);
	gtk_container_add (GTK_CONTAINER (field_view), alignment);
	gtk_widget_show (alignment);

	if (!field)
		return;

	table = gtk_table_new (13, 2, FALSE);
	gtk_table_set_col_spacings (GTK_TABLE (table), 6);
	gtk_table_set_row_spacings (GTK_TABLE (table), 6);

	text = poppler_form_field_get_name (field);
	if (text) {
		pgd_table_add_property (GTK_TABLE (table), "<b>Name:</b>", text, &row);
		g_free (text);
	}
	text = poppler_form_field_get_partial_name (field);
	if (text) {
		pgd_table_add_property (GTK_TABLE (table), "<b>Partial Name:</b>", text, &row);
		g_free (text);
	}
	text = poppler_form_field_get_mapping_name (field);
	if (text) {
		pgd_table_add_property (GTK_TABLE (table), "<b>Mapping Name:</b>", text, &row);
		g_free (text);
	}

	switch (poppler_form_field_get_field_type (field)) {
	case POPPLER_FORM_FIELD_BUTTON:
		enum_value = g_enum_get_value ((GEnumClass *) g_type_class_ref (POPPLER_TYPE_FORM_BUTTON_TYPE),
					       poppler_form_field_button_get_button_type (field));
		pgd_table_add_property (GTK_TABLE (table), "<b>Button Type:</b>", enum_value->value_name, &row);
		pgd_table_add_property (GTK_TABLE (table), "<b>Button State:</b>",
					poppler_form_field_button_get_state (field) ? "Active" : "Inactive", &row);
		break;
	case POPPLER_FORM_FIELD_TEXT:
		enum_value = g_enum_get_value ((GEnumClass *) g_type_class_ref (POPPLER_TYPE_FORM_TEXT_TYPE),
					       poppler_form_field_text_get_text_type (field));
		pgd_table_add_property (GTK_TABLE (table), "<b>Text Type:</b>", enum_value->value_name, &row);

		text = poppler_form_field_text_get_text (field);
		pgd_table_add_property (GTK_TABLE (table), "<b>Contents:</b>", text, &row);
		g_free (text);

		text = g_strdup_printf ("%d", poppler_form_field_text_get_max_len (field));
		pgd_table_add_property (GTK_TABLE (table), "<b>Max Length:</b>", text, &row);
		g_free (text);

		pgd_table_add_property (GTK_TABLE (table), "<b>Do spellcheck:</b>",
					poppler_form_field_text_do_spell_check (field) ? "Yes" : "No", &row);
		pgd_table_add_property (GTK_TABLE (table), "<b>Do scroll:</b>",
					poppler_form_field_text_do_scroll (field) ? "Yes" : "No", &row);
		pgd_table_add_property (GTK_TABLE (table), "<b>Rich Text:</b>",
					poppler_form_field_text_is_rich_text (field) ? "Yes" : "No", &row);
		pgd_table_add_property (GTK_TABLE (table), "<b>Pasword type:</b>",
					poppler_form_field_text_is_password (field) ? "Yes" : "No", &row);
		break;
	case POPPLER_FORM_FIELD_CHOICE: {
		gchar *item;
		gint   selected;
		
		enum_value = g_enum_get_value ((GEnumClass *) g_type_class_ref (POPPLER_TYPE_FORM_CHOICE_TYPE),
					       poppler_form_field_choice_get_choice_type (field));
		pgd_table_add_property (GTK_TABLE (table), "<b>Choice Type:</b>", enum_value->value_name, &row);
		pgd_table_add_property (GTK_TABLE (table), "<b>Editable:</b>",
					poppler_form_field_choice_is_editable (field) ? "Yes" : "No", &row);
		pgd_table_add_property (GTK_TABLE (table), "<b>Multiple Selection:</b>",
					poppler_form_field_choice_can_select_multiple (field) ? "Yes" : "No", &row);
		pgd_table_add_property (GTK_TABLE (table), "<b>Do spellcheck:</b>",
					poppler_form_field_choice_do_spell_check (field) ? "Yes" : "No", &row);
		pgd_table_add_property (GTK_TABLE (table), "<b>Commit on Change:</b>",
					poppler_form_field_choice_commit_on_change (field) ? "Yes" : "No", &row);

		text = g_strdup_printf ("%d", poppler_form_field_choice_get_n_items (field));
		pgd_table_add_property (GTK_TABLE (table), "<b>Number of items:</b>", text, &row);
		g_free (text);

		pgd_form_field_view_add_choice_items (GTK_TABLE (table), field, &selected, &row);

		if (poppler_form_field_choice_get_n_items (field) > selected) {
			item = poppler_form_field_choice_get_item (field, selected);
			text = g_strdup_printf ("%d (%s)", selected, item);
			g_free (item);
			pgd_table_add_property (GTK_TABLE (table), "<b>Selected item:</b>", text, &row);
			g_free (text);
		}

		text = poppler_form_field_choice_get_text (field);
		pgd_table_add_property (GTK_TABLE (table), "<b>Contents:</b>", text, &row);
		g_free (text);
	}
		break;
	case POPPLER_FORM_FIELD_SIGNATURE:
	case POPPLER_FORM_FIELD_UNKNOWN:
		break;
	default:
		g_assert_not_reached ();
	}

	gtk_container_add (GTK_CONTAINER (alignment), table);
	gtk_widget_show (table);
}