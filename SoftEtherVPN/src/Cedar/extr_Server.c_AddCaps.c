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
struct TYPE_3__ {int /*<<< orphan*/  CapsList; } ;
typedef  TYPE_1__ CAPSLIST ;
typedef  int /*<<< orphan*/  CAPS ;

/* Variables and functions */
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void AddCaps(CAPSLIST *caps, CAPS *c)
{
	// Validate arguments
	if (caps == NULL || c == NULL)
	{
		return;
	}

	Insert(caps->CapsList, c);
}