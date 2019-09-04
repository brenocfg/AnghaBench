#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gboolean ;
struct TYPE_12__ {int x; int y; } ;
struct TYPE_9__ {int x; int y; } ;
struct TYPE_10__ {int x; } ;
struct TYPE_11__ {scalar_t__ selections_idle; int scale; int /*<<< orphan*/  selection_region; TYPE_1__ stop; TYPE_2__ start; int /*<<< orphan*/  page; } ;
typedef  TYPE_3__ PgdSelectionsDemo ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  TYPE_4__ GdkEventMotion ;
typedef  int /*<<< orphan*/  GSourceFunc ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GDK_LAST_CURSOR ; 
 int /*<<< orphan*/  GDK_XTERM ; 
 scalar_t__ TRUE ; 
 scalar_t__ cairo_region_contains_point (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ g_idle_add (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ pgd_selections_render_selections ; 
 int /*<<< orphan*/  pgd_selections_update_cursor (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean
pgd_selections_drawing_area_motion_notify (GtkWidget         *area,
					   GdkEventMotion    *event,
					   PgdSelectionsDemo *demo)
{
	if (!demo->page)
		return FALSE;

	if (demo->start.x != -1) {
		demo->stop.x = event->x;
		demo->stop.y = event->y;
		if (demo->selections_idle == 0) {
			demo->selections_idle =
				g_idle_add ((GSourceFunc)pgd_selections_render_selections,
					    demo);
		}
	} else {
		gboolean over_text;

		over_text = cairo_region_contains_point (demo->selection_region,
                                                         event->x / demo->scale,
                                                         event->y / demo->scale);
		pgd_selections_update_cursor (demo, over_text ? GDK_XTERM : GDK_LAST_CURSOR);
	}

	return TRUE;
}