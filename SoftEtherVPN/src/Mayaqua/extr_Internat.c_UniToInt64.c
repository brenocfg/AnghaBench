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
typedef  int /*<<< orphan*/  UINT64 ;

/* Variables and functions */
 int MAX_SIZE ; 
 int /*<<< orphan*/  ToInt64 (char*) ; 
 int /*<<< orphan*/  UniToStrForSingleChars (char*,int,int /*<<< orphan*/ *) ; 

UINT64 UniToInt64(wchar_t *str)
{
	char tmp[MAX_SIZE];
	// Validate arguments
	if (str == NULL)
	{
		return 0;
	}

	UniToStrForSingleChars(tmp, sizeof(tmp), str);

	return ToInt64(tmp);
}