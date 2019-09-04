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
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int MAX_SIZE ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ToStr3 (char*,int,int /*<<< orphan*/ ) ; 

void UniToStr3(wchar_t *str, UINT size, UINT64 value)
{
	char tmp[MAX_SIZE];
	// Validate arguments
	if (str == NULL)
	{
		return;
	}

	ToStr3(tmp, sizeof(tmp), value);

	StrToUni(str, size, tmp);
}