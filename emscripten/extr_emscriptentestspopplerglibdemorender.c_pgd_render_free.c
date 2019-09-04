#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * pixbuf; int /*<<< orphan*/ * surface; int /*<<< orphan*/ * doc; } ;
typedef  TYPE_1__ PgdRenderDemo ;

/* Variables and functions */
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_render_free (PgdRenderDemo *demo)
{
	if (!demo)
		return;

	if (demo->doc) {
		g_object_unref (demo->doc);
		demo->doc = NULL;
	}
	
	if (demo->surface) {
		cairo_surface_destroy (demo->surface);
		demo->surface = NULL;
	}

	if (demo->pixbuf) {
		g_object_unref (demo->pixbuf);
		demo->pixbuf = NULL;
	}

	g_free (demo);
}