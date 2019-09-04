#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_9__ {int button; int type; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_7__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_8__ {int /*<<< orphan*/  style; TYPE_1__ start; TYPE_1__ stop; int /*<<< orphan*/  page; } ;
typedef  TYPE_2__ PgdSelectionsDemo ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  TYPE_3__ GdkEventButton ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  GDK_2BUTTON_PRESS 129 
#define  GDK_3BUTTON_PRESS 128 
 int /*<<< orphan*/  POPPLER_SELECTION_GLYPH ; 
 int /*<<< orphan*/  POPPLER_SELECTION_LINE ; 
 int /*<<< orphan*/  POPPLER_SELECTION_WORD ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  pgd_selections_render_selections (TYPE_2__*) ; 

__attribute__((used)) static gboolean
pgd_selections_drawing_area_button_press (GtkWidget         *area,
					  GdkEventButton    *event,
					  PgdSelectionsDemo *demo)
{
	if (!demo->page)
		return FALSE;

	if (event->button != 1)
		return FALSE;

	demo->start.x = event->x;
	demo->start.y = event->y;
	demo->stop = demo->start;

	switch (event->type) {
	case GDK_2BUTTON_PRESS:
		demo->style = POPPLER_SELECTION_WORD;
		break;
	case GDK_3BUTTON_PRESS:
		demo->style = POPPLER_SELECTION_LINE;
		break;
	default:
		demo->style = POPPLER_SELECTION_GLYPH;
	}

	pgd_selections_render_selections (demo);

	return TRUE;
}