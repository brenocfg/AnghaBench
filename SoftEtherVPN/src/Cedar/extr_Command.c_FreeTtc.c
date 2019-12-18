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
typedef  scalar_t__ UINT ;
struct TYPE_4__ {scalar_t__ ErrorCode; int /*<<< orphan*/  InitedEvent; int /*<<< orphan*/  Result; int /*<<< orphan*/  Print; int /*<<< orphan*/  Param; int /*<<< orphan*/  Thread; } ;
typedef  int /*<<< orphan*/  TT_RESULT ;
typedef  TYPE_1__ TTC ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TtPrint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _UU (char*) ; 

UINT FreeTtc(TTC *ttc, TT_RESULT *result)
{
	UINT ret;
	// Validate arguments
	if (ttc == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	WaitThread(ttc->Thread, INFINITE);
	ReleaseThread(ttc->Thread);

	TtPrint(ttc->Param, ttc->Print, _UU("TTC_FREE"));

	ret = ttc->ErrorCode;

	if (ret == ERR_NO_ERROR)
	{
		if (result != NULL)
		{
			Copy(result, &ttc->Result, sizeof(TT_RESULT));
		}
	}

	ReleaseEvent(ttc->InitedEvent);

	Free(ttc);

	return ret;
}