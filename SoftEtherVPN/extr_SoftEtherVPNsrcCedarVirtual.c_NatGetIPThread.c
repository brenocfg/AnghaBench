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
struct TYPE_3__ {int /*<<< orphan*/  ref; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  Ip; int /*<<< orphan*/  Ok; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ NAT_DNS_QUERY ;

/* Variables and functions */
 int /*<<< orphan*/  AddWaitThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DelWaitThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  GetIP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ Release (int /*<<< orphan*/ ) ; 

void NatGetIPThread(THREAD *t, void *param)
{
	NAT_DNS_QUERY *q;
	// Validate arguments
	if (t == NULL || param == NULL)
	{
		return;
	}

	q = (NAT_DNS_QUERY *)param;
	AddWaitThread(t);

	q->Ok = GetIP(&q->Ip, q->Hostname);

	DelWaitThread(t);

	if (Release(q->ref) == 0)
	{
		Free(q);
	}
}