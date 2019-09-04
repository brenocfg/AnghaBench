#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ EVENT ;

/* Variables and functions */
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_NEWEVENT_COUNT ; 
 TYPE_1__* Malloc (int) ; 
 int /*<<< orphan*/  NewRef () ; 
 int /*<<< orphan*/  OSInitEvent (TYPE_1__*) ; 

EVENT *NewEvent()
{
	// Memory allocation
	EVENT *e = Malloc(sizeof(EVENT));

	// Reference counter
	e->ref = NewRef();

	// Event initialization
	OSInitEvent(e);

	// KS
	KS_INC(KS_NEWEVENT_COUNT);

	return e;
}