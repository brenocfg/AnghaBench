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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int /*<<< orphan*/  LastError; } ;
typedef  TYPE_1__ PT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_INTERNAL_ERROR ; 
 int /*<<< orphan*/  FreePt (TYPE_1__*) ; 
 TYPE_1__* NewPt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PtMain (TYPE_1__*) ; 

UINT PtConnect(CONSOLE *c, wchar_t *cmdline)
{
	PT *pt;
	UINT ret = 0;
	// Validate arguments
	if (c == NULL)
	{
		return ERR_INTERNAL_ERROR;
	}

	pt = NewPt(c, cmdline);

	PtMain(pt);

	ret = pt->LastError;

	FreePt(pt);

	return ret;
}