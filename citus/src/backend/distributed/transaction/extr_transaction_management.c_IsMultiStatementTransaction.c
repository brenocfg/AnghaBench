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

/* Variables and functions */
 scalar_t__ DoBlockLevel ; 
 scalar_t__ FunctionCallLevel ; 
 scalar_t__ FunctionOpensTransactionBlock ; 
 scalar_t__ IsTransactionBlock () ; 
 scalar_t__ StoredProcedureLevel ; 

bool
IsMultiStatementTransaction(void)
{
	if (IsTransactionBlock())
	{
		/* in a BEGIN...END block */
		return true;
	}
	else if (DoBlockLevel > 0)
	{
		/* in (a transaction within) a do block */
		return true;
	}
	else if (StoredProcedureLevel > 0)
	{
		/* in (a transaction within) a stored procedure */
		return true;
	}
	else if (FunctionCallLevel > 0 && FunctionOpensTransactionBlock)
	{
		/* in a language-handler function call, open a transaction if configured to do so */
		return true;
	}
	else
	{
		return false;
	}
}