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
typedef  int /*<<< orphan*/  dummy ;
typedef  int /*<<< orphan*/  ELEMENT ;

/* Variables and functions */
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

ELEMENT *ElementNullSafe(ELEMENT *p)
{
	static ELEMENT dummy;
	if (p == NULL)
	{
		Zero(&dummy, sizeof(dummy));
		return &dummy;
	}
	return p;
}