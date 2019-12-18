#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ Now; scalar_t__ NextArpTablePolling; } ;
typedef  TYPE_1__ VH ;
typedef  scalar_t__ UINT64 ;

/* Variables and functions */
 scalar_t__ ARP_ENTRY_POLLING_TIME ; 
 int /*<<< orphan*/  RefreshArpTable (TYPE_1__*) ; 

void PollingArpTable(VH *v)
{
	// Validate arguments
	if (v == NULL)
	{
		return;
	}

	if (v->Now > v->NextArpTablePolling)
	{
		v->NextArpTablePolling = v->Now + (UINT64)ARP_ENTRY_POLLING_TIME;
		RefreshArpTable(v);
	}
}