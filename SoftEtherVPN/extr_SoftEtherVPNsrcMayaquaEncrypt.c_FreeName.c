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
struct TYPE_4__ {struct TYPE_4__* Local; struct TYPE_4__* State; struct TYPE_4__* Country; struct TYPE_4__* Unit; struct TYPE_4__* Organization; struct TYPE_4__* CommonName; } ;
typedef  TYPE_1__ NAME ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 

void FreeName(NAME *n)
{
	// Validate arguments
	if (n == NULL)
	{
		return;
	}

	// Release the string
	Free(n->CommonName);
	Free(n->Organization);
	Free(n->Unit);
	Free(n->Country);
	Free(n->State);
	Free(n->Local);

	// Release the object
	Free(n);

	return;
}