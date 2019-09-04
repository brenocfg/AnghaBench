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
struct TYPE_4__ {scalar_t__ idle_id; int /*<<< orphan*/ * doc; } ;
typedef  TYPE_1__ PgdFontsDemo ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_source_remove (scalar_t__) ; 

__attribute__((used)) static void
pgd_fonts_free (PgdFontsDemo *demo)
{
	if (!demo)
		return;

	if (demo->idle_id > 0) {
		g_source_remove (demo->idle_id);
		demo->idle_id = 0;
	}
	
	if (demo->doc) {
		g_object_unref (demo->doc);
		demo->doc = NULL;
	}

	g_free (demo);
}