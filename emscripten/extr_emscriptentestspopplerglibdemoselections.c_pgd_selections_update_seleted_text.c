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
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_3__ {int /*<<< orphan*/ * selected_text; int /*<<< orphan*/  doc_area; int /*<<< orphan*/  style; int /*<<< orphan*/  page; scalar_t__ selected_region; } ;
typedef  TYPE_1__ PgdSelectionsDemo ;
typedef  int /*<<< orphan*/  GList ;

/* Variables and functions */
 int /*<<< orphan*/  G_NORMALIZE_NFKC ; 
 int /*<<< orphan*/  cairo_region_destroy (scalar_t__) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_utf8_normalize (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ poppler_page_get_selected_region (int /*<<< orphan*/ ,double,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * poppler_page_get_selected_text (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_selections_update_seleted_text (PgdSelectionsDemo *demo)
{
	GList *region;
	gchar *text;

	if (demo->selected_region)
		cairo_region_destroy (demo->selected_region);
	demo->selected_region = poppler_page_get_selected_region (demo->page,
                                                                  1.0,
                                                                  demo->style,
                                                                  &demo->doc_area);
	if (demo->selected_text)
		g_free (demo->selected_text);
	demo->selected_text = NULL;

	text = poppler_page_get_selected_text (demo->page,
					       demo->style,
					       &demo->doc_area);
	if (text) {
		demo->selected_text = g_utf8_normalize (text, -1, G_NORMALIZE_NFKC);
		g_free (text);
	}
}