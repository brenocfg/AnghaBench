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
typedef  scalar_t__ UCHAR ;

/* Variables and functions */
 int COMPARE_RET (char,char) ; 
 char ToUpper (char) ; 

int CmpCaseIgnore(void *p1, void *p2, UINT size)
{
	UINT i;
	// Validate arguments
	if (p1 == NULL || p2 == NULL || size == 0)
	{
		return 0;
	}

	for (i = 0;i < size;i++)
	{
		char c1 = (char)(*(((UCHAR *)p1) + i));
		char c2 = (char)(*(((UCHAR *)p2) + i));

		c1 = ToUpper(c1);
		c2 = ToUpper(c2);

		if (c1 != c2)
		{
			return COMPARE_RET(c1, c2);
		}
	}

	return 0;
}