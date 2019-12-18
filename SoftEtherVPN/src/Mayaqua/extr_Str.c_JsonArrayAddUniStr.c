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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  JSON_ARRAY ;

/* Variables and functions */
 char* CopyUniToUtf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  JsonArrayAddStr (int /*<<< orphan*/ *,char*) ; 

UINT JsonArrayAddUniStr(JSON_ARRAY *array, wchar_t *string)
{
	UINT ret;
	char *utf8 = CopyUniToUtf(string);

	ret = JsonArrayAddStr(array, utf8);

	Free(utf8);
	return ret;
}