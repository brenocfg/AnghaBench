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
typedef  int /*<<< orphan*/  X ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  GetPrintNameFromX (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  UniToStr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void GetPrintNameFromXA(char *str, UINT size, X *x)
{
	wchar_t tmp[MAX_SIZE];
	// Validate arguments
	if (str == NULL || x == NULL)
	{
		return;
	}

	GetPrintNameFromX(tmp, sizeof(tmp), x);

	UniToStr(str, size, tmp);
}