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
struct TYPE_4__ {scalar_t__ idle_id; } ;
typedef  TYPE_1__ PgdTransitionsDemo ;
typedef  int /*<<< orphan*/  GtkButton ;
typedef  int /*<<< orphan*/  GSourceFunc ;

/* Variables and functions */
 scalar_t__ g_idle_add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  g_source_remove (scalar_t__) ; 
 scalar_t__ pgd_transitions_fill_model ; 

__attribute__((used)) static void
pgd_transitions_scan_button_clicked (GtkButton          *button,
				     PgdTransitionsDemo *demo)
{
	if (demo->idle_id > 0)
		g_source_remove (demo->idle_id);
	
	demo->idle_id = g_idle_add ((GSourceFunc)pgd_transitions_fill_model, demo);
}