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
typedef  int /*<<< orphan*/  PRAND ;

/* Variables and functions */
 int PRandInt (int /*<<< orphan*/ *) ; 

UINT GenerateDummyMark(PRAND *p)
{
	UINT i;
	if (p == NULL)
	{
		return 0;
	}

	while (true)
	{
		i = PRandInt(p);

		if (i >= 1000000000 && i <= 0x7FFFFFFE)
		{
			return i;
		}
	}

	return 0;
}