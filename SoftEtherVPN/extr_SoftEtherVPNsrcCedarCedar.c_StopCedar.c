#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int Halt; } ;
typedef  TYPE_1__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  L3FreeAllSw (TYPE_1__*) ; 
 int /*<<< orphan*/  StopAllConnection (TYPE_1__*) ; 
 int /*<<< orphan*/  StopAllHub (TYPE_1__*) ; 
 int /*<<< orphan*/  StopAllListener (TYPE_1__*) ; 

void StopCedar(CEDAR *c)
{
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	// Stop flag
	c->Halt = true;

	// Stop all listener
	StopAllListener(c);
	// Stop all connections
	StopAllConnection(c);
	// Stop all hubs
	StopAllHub(c);
	// Free all virtual L3 switch
	L3FreeAllSw(c);
}