#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ArpWaitTable; } ;
typedef  TYPE_1__ VH ;
typedef  int /*<<< orphan*/  ARP_WAIT ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void InsertArpWaitTable(VH *v, ARP_WAIT *w)
{
	// Validate arguments
	if (v == NULL || w == NULL)
	{
		return;
	}

	Add(v->ArpWaitTable, w);
}