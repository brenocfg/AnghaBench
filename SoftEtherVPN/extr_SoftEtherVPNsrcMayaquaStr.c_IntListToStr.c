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
typedef  int UINT ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  ClearStr (char*,int) ; 
 scalar_t__ IsEmptyStr (char*) ; 
 int* LIST_DATA (int /*<<< orphan*/ *,int) ; 
 int LIST_NUM (int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  StrCat (char*,int,char*) ; 
 int /*<<< orphan*/  ToStr (char*,int) ; 

void IntListToStr(char *str, UINT str_size, LIST *o, char *separate_str)
{
	UINT i;
	ClearStr(str, str_size);
	// Validate arguments
	if (o == NULL)
	{
		return;
	}
	if (IsEmptyStr(separate_str))
	{
		separate_str = ", ";
	}

	for (i = 0;i < LIST_NUM(o);i++)
	{
		char tmp[MAX_SIZE];
		UINT *v = LIST_DATA(o, i);

		ToStr(tmp, *v);

		StrCat(str, str_size, tmp);

		if (i != (LIST_NUM(o) - 1))
		{
			StrCat(str, str_size, separate_str);
		}
	}
}