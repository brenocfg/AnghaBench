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
typedef  int /*<<< orphan*/  VH ;
struct TYPE_4__ {int DnsPollingFlag; int DisconnectNow; scalar_t__ DnsFinished; } ;
typedef  TYPE_1__ NAT_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  SendNatDnsResponse (int /*<<< orphan*/ *,TYPE_1__*) ; 

void PollingNatDns(VH *v, NAT_ENTRY *n)
{
	// Validate arguments
	if (v == NULL || n == NULL)
	{
		return;
	}

	if (n->DnsFinished)
	{
		if (n->DnsPollingFlag == false)
		{
			n->DnsPollingFlag = true;
			// Process has been completed
			SendNatDnsResponse(v, n);

			// Terminating
			n->DisconnectNow = true;
		}
	}
}