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
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_ALLPROCLIST ; 
 int /*<<< orphan*/  proc_iterate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifnet*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shutdown_sockets_on_interface_proc_callout ; 

void
shutdown_sockets_on_interface(struct ifnet *ifp)
{
	proc_iterate(PROC_ALLPROCLIST,
		shutdown_sockets_on_interface_proc_callout,
		ifp, NULL, NULL);
}