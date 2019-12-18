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
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_5__ {int /*<<< orphan*/  (* Write ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ CONSOLE ;

/* Variables and functions */
 scalar_t__ IsEmptyUniStr (int /*<<< orphan*/ *) ; 
 int IsFileExistsW (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ *) ; 

bool CmdEvalIsFile(CONSOLE *c, wchar_t *str, void *param)
{
	wchar_t tmp[MAX_PATH];
	// Validate arguments
	if (c == NULL || str == NULL)
	{
		return false;
	}

	UniStrCpy(tmp, sizeof(tmp), str);

	if (IsEmptyUniStr(tmp))
	{
		c->Write(c, _UU("CMD_FILE_NAME_EMPTY"));
		return false;
	}

	if (IsFileExistsW(tmp) == false)
	{
		wchar_t tmp2[MAX_SIZE];

		UniFormat(tmp2, sizeof(tmp2), _UU("CMD_FILE_NOT_FOUND"), tmp);
		c->Write(c, tmp2);

		return false;
	}

	return true;
}