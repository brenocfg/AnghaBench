#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* Sock; } ;
struct TYPE_8__ {struct TYPE_8__* Header; int /*<<< orphan*/  DataSize; int /*<<< orphan*/  Data; } ;
struct TYPE_7__ {int /*<<< orphan*/  RecvTube; } ;
typedef  TYPE_2__ TUBEDATA ;
typedef  TYPE_3__ IPC ;
typedef  int /*<<< orphan*/  BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 int /*<<< orphan*/ * NewBlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* TubeRecvAsync (int /*<<< orphan*/ ) ; 

BLOCK *IPCRecvL2(IPC *ipc)
{
	TUBEDATA *d;
	BLOCK *b;
	// Validate arguments
	if (ipc == NULL)
	{
		return NULL;
	}

	if (ipc->Sock == NULL)
	{
		return NULL;
	}

	d = TubeRecvAsync(ipc->Sock->RecvTube);

	if (d == NULL)
	{
		return NULL;
	}

	b = NewBlock(d->Data, d->DataSize, 0);

	Free(d->Header);
	Free(d);

	return b;
}