#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  page; int /*<<< orphan*/  selection_region; } ;
struct TYPE_5__ {int /*<<< orphan*/  y2; int /*<<< orphan*/  x2; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ PopplerRectangle ;
typedef  TYPE_2__ PgdSelectionsDemo ;

/* Variables and functions */
 int /*<<< orphan*/  POPPLER_SELECTION_GLYPH ; 
 int /*<<< orphan*/  cairo_region_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poppler_page_get_selected_region (int /*<<< orphan*/ ,double,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  poppler_page_get_size (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_selections_update_selection_region (PgdSelectionsDemo *demo)
{
	PopplerRectangle area = { 0, 0, 0, 0 };

	if (demo->selection_region)
		cairo_region_destroy (demo->selection_region);

	poppler_page_get_size (demo->page, &area.x2, &area.y2);
	demo->selection_region = poppler_page_get_selected_region (demo->page,
                                                                   1.0,
                                                                   POPPLER_SELECTION_GLYPH,
                                                                   &area);
}