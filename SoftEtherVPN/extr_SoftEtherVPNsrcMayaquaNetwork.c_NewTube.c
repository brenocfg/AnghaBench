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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int /*<<< orphan*/  SizeOfHeader; int /*<<< orphan*/  SockEvent; int /*<<< orphan*/  Lock; int /*<<< orphan*/  Ref; int /*<<< orphan*/  Queue; int /*<<< orphan*/  Event; } ;
typedef  TYPE_1__ TUBE ;

/* Variables and functions */
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  NewQueue () ; 
 int /*<<< orphan*/  NewRef () ; 
 int /*<<< orphan*/  NewSockEvent () ; 
 TYPE_1__* ZeroMalloc (int) ; 

TUBE *NewTube(UINT size_of_header)
{
	TUBE *t = ZeroMalloc(sizeof(TUBE));

	t->Event = NewEvent();
	t->Queue = NewQueue();
	t->Ref = NewRef();
	t->Lock = NewLock();
	t->SockEvent = NewSockEvent();

	t->SizeOfHeader = size_of_header;

	return t;
}