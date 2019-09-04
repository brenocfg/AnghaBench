#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X ;
struct TYPE_3__ {int /*<<< orphan*/  CaList; } ;
typedef  TYPE_1__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/ * FindCaSignedX (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 

bool CheckSignatureByCa(CEDAR *cedar, X *x)
{
	X *ca;
	// Validate arguments
	if (cedar == NULL || x == NULL)
	{
		return false;
	}

	// Get the CA which signed the certificate
	ca = FindCaSignedX(cedar->CaList, x);
	if (ca == NULL)
	{
		// Not found
		return false;
	}

	// Found
	FreeX(ca);
	return true;
}