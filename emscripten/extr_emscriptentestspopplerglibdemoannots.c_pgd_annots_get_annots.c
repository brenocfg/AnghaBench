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
struct TYPE_13__ {int /*<<< orphan*/  model; int /*<<< orphan*/  timer_label; int /*<<< orphan*/ * page; int /*<<< orphan*/  num_page; int /*<<< orphan*/  doc; int /*<<< orphan*/  annot_view; } ;
struct TYPE_11__ {int /*<<< orphan*/  y2; int /*<<< orphan*/  x2; int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; } ;
struct TYPE_12__ {int /*<<< orphan*/  annot; TYPE_1__ area; } ;
typedef  TYPE_2__ PopplerAnnotMapping ;
typedef  int PopplerAnnotFlag ;
typedef  TYPE_3__ PgdAnnotsDemo ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GdkPixbuf ;
typedef  int /*<<< orphan*/  GTimer ;
typedef  TYPE_4__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  ANNOTS_COLOR_COLUMN ; 
 int /*<<< orphan*/  ANNOTS_COLUMN ; 
 int /*<<< orphan*/  ANNOTS_FLAG_HIDDEN_COLUMN ; 
 int /*<<< orphan*/  ANNOTS_FLAG_INVISIBLE_COLUMN ; 
 int /*<<< orphan*/  ANNOTS_FLAG_PRINT_COLUMN ; 
 int /*<<< orphan*/  ANNOTS_TYPE_COLUMN ; 
 int /*<<< orphan*/  ANNOTS_X1_COLUMN ; 
 int /*<<< orphan*/  ANNOTS_X2_COLUMN ; 
 int /*<<< orphan*/  ANNOTS_Y1_COLUMN ; 
 int /*<<< orphan*/  ANNOTS_Y2_COLUMN ; 
 int /*<<< orphan*/  GTK_LABEL (int /*<<< orphan*/ ) ; 
 int POPPLER_ANNOT_FLAG_HIDDEN ; 
 int POPPLER_ANNOT_FLAG_INVISIBLE ; 
 int POPPLER_ANNOT_FLAG_PRINT ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ g_list_length (TYPE_4__*) ; 
 TYPE_4__* g_list_next (TYPE_4__*) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 char* g_strdup_printf (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  g_timer_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_timer_elapsed (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_timer_new () ; 
 int /*<<< orphan*/  g_timer_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_annot_color (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_annot_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_label_set_markup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_list_store_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pgd_annot_view_set_annot (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int poppler_annot_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * poppler_document_get_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poppler_page_free_annot_mapping (TYPE_4__*) ; 
 TYPE_4__* poppler_page_get_annot_mapping (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_annots_get_annots (GtkWidget     *button,
                       PgdAnnotsDemo *demo)
{
    GList       *mapping, *l;
    gint         n_fields;
    GTimer      *timer;

    gtk_list_store_clear (demo->model);
    pgd_annot_view_set_annot (demo->annot_view, NULL);

    if (demo->page) {
        g_object_unref (demo->page);
        demo->page = NULL;
    }

    demo->page = poppler_document_get_page (demo->doc, demo->num_page);
    if (!demo->page)
        return;

    timer = g_timer_new ();
    mapping = poppler_page_get_annot_mapping (demo->page);
    g_timer_stop (timer);

    n_fields = g_list_length (mapping);
    if (n_fields > 0) {
        gchar *str;

        str = g_strdup_printf ("<i>%d annots found in %.4f seconds</i>",
                               n_fields, g_timer_elapsed (timer, NULL));
        gtk_label_set_markup (GTK_LABEL (demo->timer_label), str);
        g_free (str);
    } else {
        gtk_label_set_markup (GTK_LABEL (demo->timer_label), "<i>No annots found</i>");
    }

    g_timer_destroy (timer);

    for (l = mapping; l; l = g_list_next (l)) {
        PopplerAnnotMapping *amapping;
        GtkTreeIter          iter;
        gchar               *x1, *y1, *x2, *y2;
        GdkPixbuf           *pixbuf;
	PopplerAnnotFlag     flags;

        amapping = (PopplerAnnotMapping *) l->data;

        x1 = g_strdup_printf ("%.2f", amapping->area.x1);
        y1 = g_strdup_printf ("%.2f", amapping->area.y1);
        x2 = g_strdup_printf ("%.2f", amapping->area.x2);
        y2 = g_strdup_printf ("%.2f", amapping->area.y2);

        pixbuf = get_annot_color (amapping->annot);
	flags = poppler_annot_get_flags (amapping->annot);

        gtk_list_store_append (demo->model, &iter);
        gtk_list_store_set (demo->model, &iter,
                            ANNOTS_X1_COLUMN, x1,
                            ANNOTS_Y1_COLUMN, y1,
                            ANNOTS_X2_COLUMN, x2,
                            ANNOTS_Y2_COLUMN, y2,
                            ANNOTS_TYPE_COLUMN, get_annot_type (amapping->annot),
                            ANNOTS_COLOR_COLUMN, pixbuf,
			    ANNOTS_FLAG_INVISIBLE_COLUMN, (flags & POPPLER_ANNOT_FLAG_INVISIBLE),
			    ANNOTS_FLAG_HIDDEN_COLUMN, (flags & POPPLER_ANNOT_FLAG_HIDDEN),
			    ANNOTS_FLAG_PRINT_COLUMN, (flags & POPPLER_ANNOT_FLAG_PRINT),
                            ANNOTS_COLUMN, amapping->annot,
                           -1);

        if (pixbuf)
            g_object_unref (pixbuf);

        g_free (x1);
        g_free (y1);
        g_free (x2);
        g_free (y2);
    }

    poppler_page_free_annot_mapping (mapping);
}