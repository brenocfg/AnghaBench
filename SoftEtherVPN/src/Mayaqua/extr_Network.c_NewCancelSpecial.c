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
struct TYPE_4__ {int SpecialFlag; int pipe_read; int pipe_write; scalar_t__ hEvent; int /*<<< orphan*/  ref; } ;
typedef  scalar_t__ HANDLE ;
typedef  TYPE_1__ CANCEL ;

/* Variables and functions */
 int /*<<< orphan*/  NewRef () ; 
 TYPE_1__* ZeroMalloc (int) ; 

CANCEL *NewCancelSpecial(void *hEvent)
{
	CANCEL *c;
	// Validate arguments
	if (hEvent == NULL)
	{
		return NULL;
	}

	c = ZeroMalloc(sizeof(CANCEL));
	c->ref = NewRef();
	c->SpecialFlag = true;

#ifdef	OS_WIN32
	c->hEvent = (HANDLE)hEvent;
#else	// OS_WIN32
	c->pipe_read = (int)hEvent;
	c->pipe_write = -1;
#endif	// OS_WIN32

	return c;
}