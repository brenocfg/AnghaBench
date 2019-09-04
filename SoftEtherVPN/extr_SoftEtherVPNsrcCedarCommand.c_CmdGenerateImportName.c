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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  REMOTE_CLIENT ;

/* Variables and functions */
 int CmdIsAccountName (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _UU (char*) ; 

void CmdGenerateImportName(REMOTE_CLIENT *r, wchar_t *name, UINT size, wchar_t *old_name)
{
	UINT i;
	// Validate arguments
	if (r == NULL || name == NULL || old_name == NULL)
	{
		return;
	}

	for (i = 1;;i++)
	{
		wchar_t tmp[MAX_SIZE];
		if (i == 1)
		{
			UniFormat(tmp, sizeof(tmp), _UU("CM_IMPORT_NAME_1"), old_name);
		}
		else
		{
			UniFormat(tmp, sizeof(tmp), _UU("CM_IMPORT_NAME_2"), old_name, i);
		}

		if (CmdIsAccountName(r, tmp) == false)
		{
			UniStrCpy(name, size, tmp);
			return;
		}
	}
}