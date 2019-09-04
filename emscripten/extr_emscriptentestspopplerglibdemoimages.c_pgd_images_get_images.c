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
struct TYPE_13__ {int /*<<< orphan*/  model; int /*<<< orphan*/  timer_label; int /*<<< orphan*/  page; int /*<<< orphan*/  doc; int /*<<< orphan*/  image_view; } ;
struct TYPE_11__ {int /*<<< orphan*/  y2; int /*<<< orphan*/  x2; int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; } ;
struct TYPE_12__ {int /*<<< orphan*/  image_id; TYPE_1__ area; } ;
typedef  int /*<<< orphan*/  PopplerPage ;
typedef  TYPE_2__ PopplerImageMapping ;
typedef  TYPE_3__ PgdImagesDemo ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GTimer ;
typedef  TYPE_4__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_LABEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMAGES_ID_COLUMN ; 
 int /*<<< orphan*/  IMAGES_X1_COLUMN ; 
 int /*<<< orphan*/  IMAGES_X2_COLUMN ; 
 int /*<<< orphan*/  IMAGES_Y1_COLUMN ; 
 int /*<<< orphan*/  IMAGES_Y2_COLUMN ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ g_list_length (TYPE_4__*) ; 
 TYPE_4__* g_list_next (TYPE_4__*) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 char* g_strdup_printf (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  g_timer_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_timer_elapsed (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_timer_new () ; 
 int /*<<< orphan*/  g_timer_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_label_set_markup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_list_store_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pgd_image_view_set_image (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * poppler_document_get_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poppler_page_free_image_mapping (TYPE_4__*) ; 
 TYPE_4__* poppler_page_get_image_mapping (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_images_get_images (GtkWidget     *button,
		       PgdImagesDemo *demo)
{
	PopplerPage *page;
	GList       *mapping, *l;
	gint         n_images;
	GTimer      *timer;
	
	gtk_list_store_clear (demo->model);
	pgd_image_view_set_image (demo->image_view, NULL);

	page = poppler_document_get_page (demo->doc, demo->page);
	if (!page)
		return;

	timer = g_timer_new ();
	mapping = poppler_page_get_image_mapping (page);
	g_timer_stop (timer);

	n_images = g_list_length (mapping);
	if (n_images > 0) {
		gchar *str;
		
		str = g_strdup_printf ("<i>%d images found in %.4f seconds</i>",
				       n_images, g_timer_elapsed (timer, NULL));
		gtk_label_set_markup (GTK_LABEL (demo->timer_label), str);
		g_free (str);
	} else {
		gtk_label_set_markup (GTK_LABEL (demo->timer_label), "<i>No images found</i>");
	}

	g_timer_destroy (timer);

	for (l = mapping; l; l = g_list_next (l)) {
		PopplerImageMapping *imapping;
		GtkTreeIter          iter;
		gchar               *x1, *y1, *x2, *y2;

		imapping = (PopplerImageMapping *)l->data;

		x1 = g_strdup_printf ("%.2f", imapping->area.x1);
		y1 = g_strdup_printf ("%.2f", imapping->area.y1);
		x2 = g_strdup_printf ("%.2f", imapping->area.x2);
		y2 = g_strdup_printf ("%.2f", imapping->area.y2);

		gtk_list_store_append (demo->model, &iter);
		gtk_list_store_set (demo->model, &iter,
				    IMAGES_ID_COLUMN, imapping->image_id,
				    IMAGES_X1_COLUMN, x1, 
				    IMAGES_Y1_COLUMN, y1,
				    IMAGES_X2_COLUMN, x2,
				    IMAGES_Y2_COLUMN, y2,
				    -1);
		g_free (x1);
		g_free (y1);
		g_free (x2);
		g_free (y2);
	}

	poppler_page_free_image_mapping (mapping);
	g_object_unref (page);
}