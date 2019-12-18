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
struct omap_mbox {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap_mbox_fini (struct omap_mbox*) ; 

void omap_mbox_put(struct omap_mbox *mbox)
{
	omap_mbox_fini(mbox);
}