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
struct proc_pidcoalitioninfo {int /*<<< orphan*/  coalition_id; } ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct proc_pidcoalitioninfo*,int) ; 
 int /*<<< orphan*/  proc_coalitionids (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
proc_pidcoalitioninfo(proc_t p, struct proc_pidcoalitioninfo *ppci)
{
	bzero(ppci, sizeof(*ppci));
	proc_coalitionids(p, ppci->coalition_id);
}