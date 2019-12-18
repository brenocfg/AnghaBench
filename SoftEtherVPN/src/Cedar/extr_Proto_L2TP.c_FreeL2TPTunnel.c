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
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int /*<<< orphan*/  RecvQueue; int /*<<< orphan*/  SendQueue; int /*<<< orphan*/  SessionList; } ;
typedef  TYPE_1__ L2TP_TUNNEL ;
typedef  int /*<<< orphan*/  L2TP_SESSION ;
typedef  int /*<<< orphan*/  L2TP_QUEUE ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeL2TPQueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeL2TPSession (int /*<<< orphan*/ *) ; 
 void* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 

void FreeL2TPTunnel(L2TP_TUNNEL *t)
{
	UINT i;
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	for (i = 0;i < LIST_NUM(t->SessionList);i++)
	{
		L2TP_SESSION *s = LIST_DATA(t->SessionList, i);

		FreeL2TPSession(s);
	}

	ReleaseList(t->SessionList);

	for (i = 0;i < LIST_NUM(t->SendQueue);i++)
	{
		L2TP_QUEUE *q = LIST_DATA(t->SendQueue, i);

		FreeL2TPQueue(q);
	}

	ReleaseList(t->SendQueue);

	for (i = 0;i < LIST_NUM(t->RecvQueue);i++)
	{
		L2TP_QUEUE *q = LIST_DATA(t->RecvQueue, i);

		FreeL2TPQueue(q);
	}

	ReleaseList(t->RecvQueue);

	Free(t);
}