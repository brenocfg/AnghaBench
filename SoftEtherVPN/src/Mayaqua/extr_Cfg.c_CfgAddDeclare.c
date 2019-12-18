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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddLine (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 char* CfgEscape (char*) ; 
 int /*<<< orphan*/  Format (char*,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 char* Malloc (scalar_t__) ; 
 scalar_t__ StrLen (char*) ; 
 char* TAG_DECLARE ; 

void CfgAddDeclare(BUF *b, char *name, UINT depth)
{
	char *tmp;
	char *name2;
	UINT tmp_size;
	// Validate arguments
	if (b == NULL || name == NULL)
	{
		return;
	}

	name2 = CfgEscape(name);

	tmp_size = StrLen(name2) + 2 + StrLen(TAG_DECLARE);
	tmp = Malloc(tmp_size);

	Format(tmp, 0, "%s %s", TAG_DECLARE, name2);
	CfgAddLine(b, tmp, depth);
	CfgAddLine(b, "{", depth);
	Free(tmp);
	Free(name2);
}