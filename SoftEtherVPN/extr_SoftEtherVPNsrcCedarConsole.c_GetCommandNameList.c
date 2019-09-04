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
typedef  int /*<<< orphan*/  TOKEN_LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NullToken () ; 
 int /*<<< orphan*/  ParseCommandEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 

TOKEN_LIST *GetCommandNameList(wchar_t *str)
{
	TOKEN_LIST *t;
	// Validate arguments
	if (str == NULL)
	{
		return NullToken();
	}

	Free(ParseCommandEx(str, L"dummy_str", &t));

	return t;
}