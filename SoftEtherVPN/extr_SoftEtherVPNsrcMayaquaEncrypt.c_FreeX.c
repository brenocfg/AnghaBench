#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int do_not_free; int /*<<< orphan*/  x509; int /*<<< orphan*/  serial; } ;
typedef  TYPE_1__ X ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeX509 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeXNames (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeXSerial (int /*<<< orphan*/ ) ; 

void FreeX(X *x)
{
	// Validate arguments
	if (x == NULL)
	{
		return;
	}

	// Release the name
	FreeXNames(x);


	// Release the Serial
	FreeXSerial(x->serial);

	if (x->do_not_free == false)
	{
		FreeX509(x->x509);
	}
	Free(x);
}