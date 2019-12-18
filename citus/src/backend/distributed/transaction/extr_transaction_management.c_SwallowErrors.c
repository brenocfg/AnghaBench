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
struct TYPE_4__ {scalar_t__ elevel; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ ErrorData ;

/* Variables and functions */
 TYPE_1__* CopyErrorData () ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 scalar_t__ ERROR ; 
 int /*<<< orphan*/  FlushErrorState () ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_RE_THROW () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  ThrowErrorData (TYPE_1__*) ; 
 scalar_t__ WARNING ; 

__attribute__((used)) static void
SwallowErrors(void (*func)())
{
	MemoryContext savedContext = CurrentMemoryContext;

	PG_TRY();
	{
		func();
	}
	PG_CATCH();
	{
		ErrorData *edata = CopyErrorData();

		/* don't try to intercept PANIC or FATAL, let those breeze past us */
		if (edata->elevel != ERROR)
		{
			PG_RE_THROW();
		}

		/* turn the ERROR into a WARNING and emit it */
		edata->elevel = WARNING;
		ThrowErrorData(edata);

		/* leave the error handling system */
		FlushErrorState();
		MemoryContextSwitchTo(savedContext);
	}
	PG_END_TRY();
}