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
struct TYPE_4__ {int /*<<< orphan*/  SaverThread; int /*<<< orphan*/  SaverHalter; } ;
typedef  TYPE_1__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CiSaverThread ; 
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/  NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ ) ; 

void CiInitSaver(CLIENT *c)
{
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	c->SaverHalter = NewEvent();

	c->SaverThread = NewThread(CiSaverThread, c);
	WaitThreadInit(c->SaverThread);
}