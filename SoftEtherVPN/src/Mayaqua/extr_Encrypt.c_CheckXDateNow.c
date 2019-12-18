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
typedef  int /*<<< orphan*/  X ;

/* Variables and functions */
 int CheckXDate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemTime64 () ; 

bool CheckXDateNow(X *x)
{
	// Validate arguments
	if (x == NULL)
	{
		return false;
	}

	return CheckXDate(x, SystemTime64());
}