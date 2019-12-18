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

/* Variables and functions */
 scalar_t__ CheckAvailableVersion (int) ; 
 scalar_t__ CheckInstalledVersion (int) ; 
 int /*<<< orphan*/  CitusHasBeenLoaded () ; 
 int /*<<< orphan*/  EnableVersionChecks ; 
 int citusVersionKnownCompatible ; 

bool
CheckCitusVersion(int elevel)
{
	if (citusVersionKnownCompatible ||
		!CitusHasBeenLoaded() ||
		!EnableVersionChecks)
	{
		return true;
	}

	if (CheckAvailableVersion(elevel) && CheckInstalledVersion(elevel))
	{
		citusVersionKnownCompatible = true;
		return true;
	}
	else
	{
		return false;
	}
}