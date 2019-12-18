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
struct TYPE_3__ {int /*<<< orphan*/  NatTable; } ;
typedef  TYPE_1__ VH ;
typedef  int /*<<< orphan*/  NAT_ENTRY ;

/* Variables and functions */
 scalar_t__ Search (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

NAT_ENTRY *SearchNat(VH *v, NAT_ENTRY *target)
{
	NAT_ENTRY *n;
	// Validate arguments
	if (v == NULL || target == NULL)
	{
		return NULL;
	}

	// Binary search
	n = (NAT_ENTRY *)Search(v->NatTable, target);

	return n;
}