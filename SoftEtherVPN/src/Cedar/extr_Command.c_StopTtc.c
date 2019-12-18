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
struct TYPE_3__ {int Halt; int /*<<< orphan*/  Print; int /*<<< orphan*/  Param; } ;
typedef  TYPE_1__ TTC ;

/* Variables and functions */
 int /*<<< orphan*/  TtPrint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _UU (char*) ; 

void StopTtc(TTC *ttc)
{
	// Validate arguments
	if (ttc == NULL)
	{
		return;
	}

	TtPrint(ttc->Param, ttc->Print, _UU("TTC_STOPPING"));

	ttc->Halt = true;
}