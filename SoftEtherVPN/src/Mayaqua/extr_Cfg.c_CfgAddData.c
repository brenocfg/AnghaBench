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
 int /*<<< orphan*/  CfgTypeToStr (scalar_t__) ; 
 int /*<<< orphan*/  Free (char*) ; 
 char* Malloc (scalar_t__) ; 
 int /*<<< orphan*/  StrCat (char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ StrLen (char*) ; 

void CfgAddData(BUF *b, UINT type, char *name, char *data, char *sub, UINT depth)
{
	char *tmp;
	char *name2;
	char *data2;
	char *sub2 = NULL;
	UINT tmp_size;
	// Validate arguments
	if (b == NULL || type == 0 || name == NULL || data == NULL)
	{
		return;
	}

	name2 = CfgEscape(name);
	data2 = CfgEscape(data);
	if (sub != NULL)
	{
		sub2 = CfgEscape(sub);
	}

	tmp_size = StrLen(name2) + StrLen(data2) + 2 + 64 + 1;
	tmp = Malloc(tmp_size);

	if (sub2 != NULL)
	{
		StrCpy(tmp, tmp_size, CfgTypeToStr(type));
		StrCat(tmp, tmp_size, " ");
		StrCat(tmp, tmp_size, name2);
		StrCat(tmp, tmp_size, " ");
		StrCat(tmp, tmp_size, data2);
		StrCat(tmp, tmp_size, " ");
		StrCat(tmp, tmp_size, sub2);
	}
	else
	{
		StrCpy(tmp, tmp_size, CfgTypeToStr(type));
		StrCat(tmp, tmp_size, " ");
		StrCat(tmp, tmp_size, name2);
		StrCat(tmp, tmp_size, " ");
		StrCat(tmp, tmp_size, data2);
	}

	Free(name2);
	Free(data2);
	if (sub2 != NULL)
	{
		Free(sub2);
	}
	CfgAddLine(b, tmp, depth);
	Free(tmp);
}