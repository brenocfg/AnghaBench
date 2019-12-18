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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  AddInt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IsIntInList (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void AddIntDistinct(LIST *o, UINT i)
{
	// Validate arguments
	if (o == NULL)
	{
		return;
	}

	if (IsIntInList(o, i) == false)
	{
		AddInt(o, i);
	}
}