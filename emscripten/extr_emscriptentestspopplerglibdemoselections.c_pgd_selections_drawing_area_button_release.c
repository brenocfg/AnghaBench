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
struct TYPE_9__ {int button; } ;
struct TYPE_7__ {int x; } ;
struct TYPE_8__ {scalar_t__ selections_idle; TYPE_1__ start; int /*<<< orphan*/  page; } ;
typedef  TYPE_2__ PgdSelectionsDemo ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  TYPE_3__ GdkEventButton ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_source_remove (scalar_t__) ; 
 int /*<<< orphan*/  pgd_selections_update_seleted_text (TYPE_2__*) ; 

__attribute__((used)) static gboolean
pgd_selections_drawing_area_button_release (GtkWidget         *area,
					    GdkEventButton    *event,
					    PgdSelectionsDemo *demo)
{
	if (!demo->page)
		return FALSE;

	if (event->button != 1)
		return FALSE;

	if (demo->start.x != -1)
		pgd_selections_update_seleted_text (demo);

	demo->start.x = -1;

	if (demo->selections_idle > 0) {
		g_source_remove (demo->selections_idle);
		demo->selections_idle = 0;
	}

	return TRUE;
}