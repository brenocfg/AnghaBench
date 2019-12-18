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
struct mibif {int /*<<< orphan*/ * xnotify_mod; int /*<<< orphan*/ * xnotify_data; int /*<<< orphan*/ * xnotify; } ;

/* Variables and functions */

void
mibif_unnotify(void *arg)
{
	struct mibif *ifp = arg;

	ifp->xnotify = NULL;
	ifp->xnotify_data = NULL;
	ifp->xnotify_mod = NULL;
}