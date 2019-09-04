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
struct TYPE_5__ {int /*<<< orphan*/  Local; int /*<<< orphan*/  State; int /*<<< orphan*/  Country; int /*<<< orphan*/  Unit; int /*<<< orphan*/  Organization; int /*<<< orphan*/  CommonName; } ;
typedef  TYPE_1__ NAME ;

/* Variables and functions */
 TYPE_1__* NewName (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

NAME *CopyName(NAME *n)
{
	// Validate arguments
	if (n == NULL)
	{
		return NULL;
	}

	return NewName(n->CommonName, n->Organization, n->Unit,
		n->Country, n->State, n->Local);
}