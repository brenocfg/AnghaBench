#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gint ;
typedef  char gchar ;
struct TYPE_14__ {scalar_t__ data; } ;
struct TYPE_13__ {int /*<<< orphan*/  model; int /*<<< orphan*/  timer_label; int /*<<< orphan*/  page; int /*<<< orphan*/  doc; int /*<<< orphan*/  field_view; } ;
struct TYPE_11__ {int /*<<< orphan*/  y2; int /*<<< orphan*/  x2; int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; } ;
struct TYPE_12__ {int /*<<< orphan*/  field; TYPE_1__ area; } ;
typedef  int /*<<< orphan*/  PopplerPage ;
typedef  TYPE_2__ PopplerFormFieldMapping ;
typedef  TYPE_3__ PgdFormsDemo ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GTimer ;
typedef  TYPE_4__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  FORMS_FIELD_COLUMN ; 
 int /*<<< orphan*/  FORMS_FIELD_TYPE_COLUMN ; 
 int /*<<< orphan*/  FORMS_ID_COLUMN ; 
 int /*<<< orphan*/  FORMS_READ_ONLY_COLUMN ; 
 int /*<<< orphan*/  FORMS_X1_COLUMN ; 
 int /*<<< orphan*/  FORMS_X2_COLUMN ; 
 int /*<<< orphan*/  FORMS_Y1_COLUMN ; 
 int /*<<< orphan*/  FORMS_Y2_COLUMN ; 
 int /*<<< orphan*/  GTK_LABEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ g_list_length (TYPE_4__*) ; 
 TYPE_4__* g_list_next (TYPE_4__*) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 char* g_strdup_printf (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  g_timer_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_timer_elapsed (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_timer_new () ; 
 int /*<<< orphan*/  g_timer_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_form_field_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_label_set_markup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_list_store_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pgd_form_field_view_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * poppler_document_get_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poppler_form_field_get_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poppler_form_field_is_read_only (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poppler_page_free_form_field_mapping (TYPE_4__*) ; 
 TYPE_4__* poppler_page_get_form_field_mapping (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_forms_get_form_fields (GtkWidget    *button,
			   PgdFormsDemo *demo)
{
	PopplerPage *page;
	GList       *mapping, *l;
	gint         n_fields;
	GTimer      *timer;
	
	gtk_list_store_clear (demo->model);
	pgd_form_field_view_set_field (demo->field_view, NULL);

	page = poppler_document_get_page (demo->doc, demo->page);
	if (!page)
		return;

	timer = g_timer_new ();
	mapping = poppler_page_get_form_field_mapping (page);
	g_timer_stop (timer);

	n_fields = g_list_length (mapping);
	if (n_fields > 0) {
		gchar *str;
		
		str = g_strdup_printf ("<i>%d form fields found in %.4f seconds</i>",
				       n_fields, g_timer_elapsed (timer, NULL));
		gtk_label_set_markup (GTK_LABEL (demo->timer_label), str);
		g_free (str);
	} else {
		gtk_label_set_markup (GTK_LABEL (demo->timer_label), "<i>No form fields found</i>");
	}

	g_timer_destroy (timer);

	for (l = mapping; l; l = g_list_next (l)) {
		PopplerFormFieldMapping *fmapping;
		GtkTreeIter              iter;
		gchar                   *x1, *y1, *x2, *y2;

		fmapping = (PopplerFormFieldMapping *)l->data;

		x1 = g_strdup_printf ("%.2f", fmapping->area.x1);
		y1 = g_strdup_printf ("%.2f", fmapping->area.y1);
		x2 = g_strdup_printf ("%.2f", fmapping->area.x2);
		y2 = g_strdup_printf ("%.2f", fmapping->area.y2);

		gtk_list_store_append (demo->model, &iter);
		gtk_list_store_set (demo->model, &iter,
				    FORMS_FIELD_TYPE_COLUMN, get_form_field_type (fmapping->field),
				    FORMS_ID_COLUMN, poppler_form_field_get_id (fmapping->field),
				    FORMS_READ_ONLY_COLUMN, poppler_form_field_is_read_only (fmapping->field),
				    FORMS_X1_COLUMN, x1, 
				    FORMS_Y1_COLUMN, y1,
				    FORMS_X2_COLUMN, x2,
				    FORMS_Y2_COLUMN, y2,
				    FORMS_FIELD_COLUMN, fmapping->field,
				    -1);
		g_free (x1);
		g_free (y1);
		g_free (x2);
		g_free (y2);
	}

	poppler_page_free_form_field_mapping (mapping);
	g_object_unref (page);
}