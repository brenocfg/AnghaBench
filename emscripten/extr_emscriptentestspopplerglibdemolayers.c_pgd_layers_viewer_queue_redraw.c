#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PgdLayersDemo ;
typedef  int /*<<< orphan*/  GSourceFunc ;

/* Variables and functions */
 int /*<<< orphan*/  g_idle_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pgd_layers_viewer_redraw ; 

__attribute__((used)) static void
pgd_layers_viewer_queue_redraw (PgdLayersDemo *demo)
{
	g_idle_add ((GSourceFunc)pgd_layers_viewer_redraw, demo);
}