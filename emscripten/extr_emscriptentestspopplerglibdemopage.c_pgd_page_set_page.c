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
typedef  int /*<<< orphan*/  gdouble ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  cairo_surface_t ;
struct TYPE_3__ {int /*<<< orphan*/  thumbnail; int /*<<< orphan*/  thumbnail_size; int /*<<< orphan*/  duration; int /*<<< orphan*/  size; int /*<<< orphan*/  label; int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  PopplerPage ;
typedef  TYPE_1__ PgdPageDemo ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_ICON_SIZE_DIALOG ; 
 int /*<<< orphan*/  GTK_IMAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_LABEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_STOCK_MISSING_IMAGE ; 
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup (char*) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  gtk_image_set_from_stock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_label_set_markup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_label_set_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  image_set_from_surface (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_page_get_duration (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_page_get_index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * poppler_page_get_label (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_page_get_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * poppler_page_get_thumbnail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_page_get_thumbnail_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_page_set_page (PgdPageDemo *demo,
		   PopplerPage *page)
{
#ifdef POPPLER_WITH_GDK
	GdkPixbuf *thumbnail;
#else
	cairo_surface_t *thumbnail;
#endif
	gchar     *str;

	str = page ? g_strdup_printf ("%d", poppler_page_get_index (page)) : NULL;
	gtk_label_set_text (GTK_LABEL (demo->index), str);
	g_free (str);

	if (page) {
		str = poppler_page_get_label (page);
		gtk_label_set_text (GTK_LABEL (demo->label), str);
		g_free (str);
	} else {
		gtk_label_set_text (GTK_LABEL (demo->label), NULL);
	}

	if (page) {
		gdouble width, height;

		poppler_page_get_size (page, &width, &height);
		str = g_strdup_printf ("%.2f x %.2f", width, height);
		gtk_label_set_text (GTK_LABEL (demo->size), str);
		g_free (str);
	} else {
		gtk_label_set_text (GTK_LABEL (demo->size), NULL);
	}

	str = page ? g_strdup_printf ("%.2f seconds", poppler_page_get_duration (page)) : NULL;
	gtk_label_set_text (GTK_LABEL (demo->duration), str);
	g_free (str);

#ifdef POPPLER_WITH_GDK
	thumbnail = page ? poppler_page_get_thumbnail_pixbuf (page) : NULL;
#else
	thumbnail = page ? poppler_page_get_thumbnail (page) : NULL;
#endif
	if (thumbnail) {
		gint width, height;
		
		poppler_page_get_thumbnail_size (page, &width, &height);
		str = g_strdup_printf ("%d x %d", width, height);
		gtk_label_set_text (GTK_LABEL (demo->thumbnail_size), str);
		g_free (str);
		
#ifdef POPPLER_WITH_GDK
		gtk_image_set_from_pixbuf (GTK_IMAGE (demo->thumbnail), thumbnail);
		g_object_unref (thumbnail);
#else
		image_set_from_surface (GTK_IMAGE (demo->thumbnail), thumbnail);
		cairo_surface_destroy (thumbnail);
#endif
	} else {
		str = g_strdup ("<i>No thumbnail found</i>");
		gtk_label_set_markup (GTK_LABEL (demo->thumbnail_size), str);
		g_free (str);

		gtk_image_set_from_stock (GTK_IMAGE (demo->thumbnail),
					  GTK_STOCK_MISSING_IMAGE,
					  GTK_ICON_SIZE_DIALOG);
	}
}