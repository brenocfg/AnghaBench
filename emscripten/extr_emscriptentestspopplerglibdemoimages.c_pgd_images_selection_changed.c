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
struct TYPE_3__ {int /*<<< orphan*/  image_view; int /*<<< orphan*/  page; int /*<<< orphan*/  doc; } ;
typedef  int /*<<< orphan*/  PopplerPage ;
typedef  TYPE_1__ PgdImagesDemo ;
typedef  int /*<<< orphan*/  GtkTreeSelection ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  IMAGES_ID_COLUMN ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ gtk_tree_selection_get_selected (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_image_view_set_image (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * poppler_document_get_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poppler_page_get_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pgd_images_selection_changed (GtkTreeSelection *treeselection,
			      PgdImagesDemo    *demo)
{
	GtkTreeModel *model;
	GtkTreeIter   iter;

	if (gtk_tree_selection_get_selected (treeselection, &model, &iter)) {
		PopplerPage *page;
		gint         image_id;

		gtk_tree_model_get (model, &iter,
				    IMAGES_ID_COLUMN, &image_id,
				    -1);
		page = poppler_document_get_page (demo->doc, demo->page);
		pgd_image_view_set_image (demo->image_view,
					  poppler_page_get_image (page, image_id));
		g_object_unref (page);
					  
	}
}