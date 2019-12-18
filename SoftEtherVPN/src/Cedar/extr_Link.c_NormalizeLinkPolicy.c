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
struct TYPE_3__ {int Access; int NoBridge; int NoRouting; int MonitorPort; int MaxConnection; int TimeOut; int FixPassword; } ;
typedef  TYPE_1__ POLICY ;

/* Variables and functions */

void NormalizeLinkPolicy(POLICY *p)
{
	// Validate arguments
	if (p == NULL)
	{
		return;
	}

	p->Access = true;
	p->NoBridge = p->NoRouting = p->MonitorPort = false;
	p->MaxConnection = 32;
	p->TimeOut = 20;
	p->FixPassword = false;
}