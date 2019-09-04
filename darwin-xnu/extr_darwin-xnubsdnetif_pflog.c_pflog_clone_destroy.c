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
 int /*<<< orphan*/  ifnet_detach (struct ifnet*) ; 
 int pflog_remove (struct ifnet*) ; 

__attribute__((used)) static int
pflog_clone_destroy(struct ifnet *ifp)
{
	int error = 0;

	if ((error = pflog_remove(ifp)) != 0)
		goto done;
	/* bpfdetach() is taken care of as part of interface detach */
	(void)ifnet_detach(ifp);
done:
	return (error);
}