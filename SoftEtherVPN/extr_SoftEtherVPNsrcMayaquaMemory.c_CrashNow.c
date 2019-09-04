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
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 scalar_t__ Rand32 () ; 
 int /*<<< orphan*/  Rand8 () ; 

void CrashNow()
{
	while (true)
	{
		UINT r = Rand32();
		UCHAR *c = (UCHAR *)r;

		*c = Rand8();
	}
}