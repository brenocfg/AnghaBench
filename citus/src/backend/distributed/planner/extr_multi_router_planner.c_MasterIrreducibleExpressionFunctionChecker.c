#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 char PROVOLATILE_IMMUTABLE ; 
 char PROVOLATILE_STABLE ; 
 char PROVOLATILE_VOLATILE ; 
 char func_volatile (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
MasterIrreducibleExpressionFunctionChecker(Oid func_id, void *context)
{
	char volatileFlag = func_volatile(func_id);
	char *volatileContext = (char *) context;

	if (volatileFlag == PROVOLATILE_VOLATILE || *volatileContext == PROVOLATILE_VOLATILE)
	{
		*volatileContext = PROVOLATILE_VOLATILE;
	}
	else if (volatileFlag == PROVOLATILE_STABLE || *volatileContext == PROVOLATILE_STABLE)
	{
		*volatileContext = PROVOLATILE_STABLE;
	}
	else
	{
		*volatileContext = PROVOLATILE_IMMUTABLE;
	}

	return (volatileFlag == PROVOLATILE_VOLATILE);
}