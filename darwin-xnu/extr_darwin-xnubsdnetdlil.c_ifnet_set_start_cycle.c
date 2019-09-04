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
struct timespec {scalar_t__ tv_nsec; } ;
struct ifnet {struct timespec if_start_cycle; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct timespec*,int) ; 
 scalar_t__ dlil_verbose ; 
 char* if_name (struct ifnet*) ; 
 int /*<<< orphan*/  printf (char*,char*,scalar_t__) ; 

void
ifnet_set_start_cycle(struct ifnet *ifp, struct timespec *ts)
{
	if (ts == NULL)
		bzero(&ifp->if_start_cycle, sizeof (ifp->if_start_cycle));
	else
		*(&ifp->if_start_cycle) = *ts;

	if (ts != NULL && ts->tv_nsec != 0 && dlil_verbose)
		printf("%s: restart interval set to %lu nsec\n",
		    if_name(ifp), ts->tv_nsec);
}