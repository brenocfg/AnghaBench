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
struct TYPE_3__ {int /*<<< orphan*/  visitedObjects; } ;
typedef  TYPE_1__ ObjectAddressCollector ;
typedef  int /*<<< orphan*/  ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_ENTER ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
MarkObjectVisited(ObjectAddressCollector *collector, const ObjectAddress *target)
{
	ObjectAddress *address = NULL;
	bool found = false;

	/* add to set */
	address = (ObjectAddress *) hash_search(collector->visitedObjects, target,
											HASH_ENTER, &found);

	if (!found)
	{
		/* copy object address in */
		*address = *target;
	}
}