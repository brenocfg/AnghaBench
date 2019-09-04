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
typedef  int /*<<< orphan*/  HUB ;

/* Variables and functions */
 int AcIsUser (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  AcLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcUnlock (int /*<<< orphan*/ *) ; 

bool SamIsUser(HUB *h, char *username)
{
	bool b;
	// Validate arguments
	if (h == NULL || username == NULL)
	{
		return false;
	}

	AcLock(h);
	{
		b = AcIsUser(h, username);
	}
	AcUnlock(h);

	return b;
}