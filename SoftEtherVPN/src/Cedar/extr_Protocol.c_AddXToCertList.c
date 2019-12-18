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
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int CheckXDateNow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CloneX (int /*<<< orphan*/ *) ; 
 scalar_t__ IsXInCertList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void AddXToCertList(LIST *o, X *x)
{
	// Validate arguments
	if (o == NULL || x == NULL)
	{
		return;
	}

	if (IsXInCertList(o, x))
	{
		return;
	}

	if (CheckXDateNow(x) == false)
	{
		return;
	}

	Add(o, CloneX(x));
}