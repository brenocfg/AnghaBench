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
struct TYPE_3__ {scalar_t__ elevel; scalar_t__ sqlerrcode; char* message; } ;
typedef  TYPE_1__ ErrorData ;

/* Variables and functions */
 scalar_t__ ERRCODE_QUERY_CANCELED ; 
 scalar_t__ ERRCODE_T_R_DEADLOCK_DETECTED ; 
 scalar_t__ ERROR ; 
 scalar_t__ MyBackendGotCancelledDueToDeadlock () ; 

__attribute__((used)) static void
multi_log_hook(ErrorData *edata)
{
	/*
	 * Show the user a meaningful error message when a backend is cancelled
	 * by the distributed deadlock detection.
	 */
	if (edata->elevel == ERROR && edata->sqlerrcode == ERRCODE_QUERY_CANCELED &&
		MyBackendGotCancelledDueToDeadlock())
	{
		edata->sqlerrcode = ERRCODE_T_R_DEADLOCK_DETECTED;
		edata->message = "canceling the transaction since it was "
						 "involved in a distributed deadlock";
	}
}