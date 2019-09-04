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
typedef  int /*<<< orphan*/  gdouble ;
struct TYPE_3__ {int /*<<< orphan*/  slice_h; int /*<<< orphan*/  slice_w; int /*<<< orphan*/  slice_y; int /*<<< orphan*/  slice_x; int /*<<< orphan*/  page; int /*<<< orphan*/  doc; } ;
typedef  int /*<<< orphan*/  PopplerPage ;
typedef  TYPE_1__ PgdRenderDemo ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_SPIN_BUTTON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_spin_button_set_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_spin_button_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * poppler_document_get_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poppler_page_get_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_render_slice_selector_setup (PgdRenderDemo *demo)
{
	PopplerPage *page;
	gdouble      width, height;

	page = poppler_document_get_page (demo->doc, demo->page);
	if (!page)
		return;

	poppler_page_get_size (page, &width, &height);
	
	gtk_spin_button_set_range (GTK_SPIN_BUTTON (demo->slice_x), 0, width);
	gtk_spin_button_set_range (GTK_SPIN_BUTTON (demo->slice_y), 0, height);
	gtk_spin_button_set_range (GTK_SPIN_BUTTON (demo->slice_w), 0, width);
	gtk_spin_button_set_range (GTK_SPIN_BUTTON (demo->slice_h), 0, height);

	gtk_spin_button_set_value (GTK_SPIN_BUTTON (demo->slice_x), 0);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (demo->slice_y), 0);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (demo->slice_w), width);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (demo->slice_h), height);

	g_object_unref (page);
}