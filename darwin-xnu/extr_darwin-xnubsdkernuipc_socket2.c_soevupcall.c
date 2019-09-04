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
typedef  int /*<<< orphan*/  u_int32_t ;
struct socket {int /*<<< orphan*/  (* so_event ) (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  so_eventmask; int /*<<< orphan*/  so_eventarg; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
soevupcall(struct socket *so, u_int32_t hint)
{
	if (so->so_event != NULL) {
		caddr_t so_eventarg = so->so_eventarg;

		hint &= so->so_eventmask;
		if (hint != 0)
			so->so_event(so, so_eventarg, hint);
	}
}