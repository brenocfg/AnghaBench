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
struct TYPE_3__ {int /*<<< orphan*/  ref; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClientAdditionalThread ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ *) ; 

void SessionAdditionalConnect(SESSION *s)
{
	THREAD *t;
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	// s->LastTryAddConnectTime = Tick64();

	AddRef(s->ref);
	t = NewThread(ClientAdditionalThread, (void *)s);
	WaitThreadInit(t);
	ReleaseThread(t);
}