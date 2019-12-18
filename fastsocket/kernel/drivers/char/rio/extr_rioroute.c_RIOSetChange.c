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
struct rio_info {scalar_t__ RIOQuickCheck; scalar_t__ RIOSignalProcess; } ;

/* Variables and functions */
 scalar_t__ CHANGED ; 
 scalar_t__ NOT_CHANGED ; 
 int /*<<< orphan*/  RIO_DEBUG_ROUTE ; 
 int /*<<< orphan*/  rio_dprintk (int /*<<< orphan*/ ,char*) ; 

int RIOSetChange(struct rio_info *p)
{
	if (p->RIOQuickCheck != NOT_CHANGED)
		return (0);
	p->RIOQuickCheck = CHANGED;
	if (p->RIOSignalProcess) {
		rio_dprintk(RIO_DEBUG_ROUTE, "Send SIG-HUP");
		/*
		   psignal( RIOSignalProcess, SIGHUP );
		 */
	}
	return (0);
}