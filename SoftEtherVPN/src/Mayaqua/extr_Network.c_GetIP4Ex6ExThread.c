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
struct TYPE_3__ {int IPv6; int /*<<< orphan*/  HostName; int /*<<< orphan*/  Ip; int /*<<< orphan*/  Ok; int /*<<< orphan*/  Ref; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ GETIP_THREAD_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AddWaitThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DelWaitThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetIP4Inner (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetIP6Inner (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoticeThreadInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseGetIPThreadParam (TYPE_1__*) ; 
 int /*<<< orphan*/  getip_thread_counter ; 

void GetIP4Ex6ExThread(THREAD *t, void *param)
{
	GETIP_THREAD_PARAM *p;
	// Validate arguments
	if (t == NULL || param == NULL)
	{
		return;
	}

	p = (GETIP_THREAD_PARAM *)param;

	AddRef(p->Ref);

	NoticeThreadInit(t);

	AddWaitThread(t);

	// Execution of resolution
	if (p->IPv6 == false)
	{
		// IPv4
		p->Ok = GetIP4Inner(&p->Ip, p->HostName);
	}
	else
	{
		// IPv6
		p->Ok = GetIP6Inner(&p->Ip, p->HostName);
	}

	ReleaseGetIPThreadParam(p);

	DelWaitThread(t);

	Dec(getip_thread_counter);
}