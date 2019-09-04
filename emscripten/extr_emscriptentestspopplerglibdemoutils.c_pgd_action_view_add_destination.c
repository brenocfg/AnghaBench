#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gint ;
typedef  char gchar ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_8__ {char* value_name; } ;
struct TYPE_7__ {scalar_t__ type; char* named_dest; scalar_t__ zoom; scalar_t__ bottom; scalar_t__ top; scalar_t__ right; scalar_t__ left; scalar_t__ page_num; } ;
typedef  int /*<<< orphan*/  PopplerPage ;
typedef  int /*<<< orphan*/  PopplerDocument ;
typedef  TYPE_1__ PopplerDest ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTable ;
typedef  TYPE_2__ GEnumValue ;
typedef  int /*<<< orphan*/  GEnumClass ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_ALIGNMENT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_TABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ POPPLER_DEST_NAMED ; 
 int /*<<< orphan*/  POPPLER_TYPE_DEST_TYPE ; 
 TYPE_2__* g_enum_get_value (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_object_get (int /*<<< orphan*/ ,char*,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_object_get_data (int /*<<< orphan*/ ,char*) ; 
 char* g_strdup_printf (char*,scalar_t__,...) ; 
 scalar_t__ g_type_class_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_alignment_new (double,double,int,int) ; 
 int /*<<< orphan*/  gtk_alignment_set_padding (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_table_attach_defaults (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * gtk_table_new (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_table_set_col_spacings (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gtk_table_set_row_spacings (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_table_add_property (int /*<<< orphan*/ *,char*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  poppler_dest_free (TYPE_1__*) ; 
 TYPE_1__* poppler_document_find_dest (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * poppler_document_get_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pgd_action_view_add_destination (GtkWidget   *action_view,
				 GtkTable    *table,
				 PopplerDest *dest,
				 gboolean     remote,
				 gint        *row)
{
	PopplerDocument *document;
	GEnumValue      *enum_value;
	gchar           *str;
	
	pgd_table_add_property (table, "<b>Type:</b>", "Destination", row);
	
	enum_value = g_enum_get_value ((GEnumClass *) g_type_class_ref (POPPLER_TYPE_DEST_TYPE), dest->type);
	pgd_table_add_property (table, "<b>Destination Type:</b>", enum_value->value_name, row);

	document = g_object_get_data (G_OBJECT (action_view), "document");
	
	if (dest->type != POPPLER_DEST_NAMED) {
		str = NULL;
		
		if (document && !remote) {
			PopplerPage *poppler_page;
			gchar       *page_label;
			
			poppler_page = poppler_document_get_page (document, MAX (0, dest->page_num - 1));
			
			g_object_get (G_OBJECT (poppler_page),
				      "label", &page_label,
				      NULL);
			if (page_label) {
				str = g_strdup_printf ("%d (%s)", dest->page_num, page_label);
				g_free (page_label);
			}
		}
		
		if (!str)
			str = g_strdup_printf ("%d", dest->page_num);
		pgd_table_add_property (table, "<b>Page:</b>", str, row);
		g_free (str);
		
		str = g_strdup_printf ("%.2f", dest->left);
		pgd_table_add_property (table, "<b>Left:</b>", str, row);
		g_free (str);
		
		str = g_strdup_printf ("%.2f", dest->right);
		pgd_table_add_property (table, "<b>Right:</b>", str, row);
		g_free (str);
		
		str = g_strdup_printf ("%.2f", dest->top);
		pgd_table_add_property (table, "<b>Top:</b>", str, row);
		g_free (str);
	
		str = g_strdup_printf ("%.2f", dest->bottom);
		pgd_table_add_property (table, "<b>Bottom:</b>", str, row);
		g_free (str);
	
		str = g_strdup_printf ("%.2f", dest->zoom);
		pgd_table_add_property (table, "<b>Zoom:</b>", str, row);
		g_free (str);
	} else {
		pgd_table_add_property (table, "<b>Named Dest:</b>", dest->named_dest, row);

		if (document && !remote) {
			PopplerDest *new_dest;

			new_dest = poppler_document_find_dest (document, dest->named_dest);
			if (new_dest) {
				GtkWidget *new_table, *alignment;
				gint       new_row = 0;

				alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
				gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 5, 5, 12, 5);
				
				new_table = gtk_table_new (8, 2, FALSE);
				gtk_table_set_col_spacings (GTK_TABLE (new_table), 6);
				gtk_table_set_row_spacings (GTK_TABLE (new_table), 6);
				gtk_table_attach_defaults (table, alignment, 0, 2, *row, *row + 1);
				gtk_widget_show (alignment);
				
				pgd_action_view_add_destination (action_view, GTK_TABLE (new_table),
								 new_dest, FALSE, &new_row);
				poppler_dest_free (new_dest);

				gtk_container_add (GTK_CONTAINER (alignment), new_table);
				gtk_widget_show (new_table);

				*row += 1;
			}
		}
	}
}