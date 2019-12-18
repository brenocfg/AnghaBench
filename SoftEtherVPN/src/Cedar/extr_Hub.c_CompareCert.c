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
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp1 ;
typedef  int /*<<< orphan*/  X ;

/* Variables and functions */
 int /*<<< orphan*/  GetPrintNameFromX (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int UniStrCmpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int CompareCert(void *p1, void *p2)
{
	X *x1, *x2;
	wchar_t tmp1[MAX_SIZE];
	wchar_t tmp2[MAX_SIZE];
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	x1 = *(X **)p1;
	x2 = *(X **)p2;
	if (x1 == NULL || x2 == NULL)
	{
		return 0;
	}

	GetPrintNameFromX(tmp1, sizeof(tmp1), x1);
	GetPrintNameFromX(tmp2, sizeof(tmp2), x2);

	return UniStrCmpi(tmp1, tmp2);
}