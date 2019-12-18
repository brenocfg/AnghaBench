#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  loc; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  abort () ; 
 int exception ; 
 TYPE_1__* handler ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 

void
exraise(int e)
{
	INTOFF;
	if (handler == NULL)
		abort();
	exception = e;
	longjmp(handler->loc, 1);
}