#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Local; int /*<<< orphan*/  State; int /*<<< orphan*/  Country; int /*<<< orphan*/  Unit; int /*<<< orphan*/  Organization; int /*<<< orphan*/  CommonName; } ;
typedef  TYPE_1__ NAME ;

/* Variables and functions */
 scalar_t__ UniStrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool CompareName(NAME *n1, NAME *n2)
{
	// Validate arguments
	if (n1 == NULL || n2 == NULL)
	{
		return false;
	}

	// Name comparison
	if (UniStrCmpi(n1->CommonName, n2->CommonName) == 0 &&
		UniStrCmpi(n1->Organization, n2->Organization) == 0 &&
		UniStrCmpi(n1->Unit, n2->Unit) == 0 &&
		UniStrCmpi(n1->Country, n2->Country) == 0 &&
		UniStrCmpi(n1->State, n2->State) == 0 &&
		UniStrCmpi(n1->Local, n2->Local) == 0)
	{
		return true;
	}

	return false;
}