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
typedef  int /*<<< orphan*/  ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  EnableDependencyCreation ; 
 int /*<<< orphan*/  IsObjectDistributed (int /*<<< orphan*/  const*) ; 
 scalar_t__ creating_extension ; 

__attribute__((used)) static bool
ShouldPropagateAlterType(const ObjectAddress *address)
{
	if (creating_extension)
	{
		/*
		 * extensions should be created separately on the workers, types cascading from an
		 * extension should therefor not be propagated.
		 */
		return false;
	}

	if (!EnableDependencyCreation)
	{
		/*
		 * we are configured to disable object propagation, should not propagate anything
		 */
		return false;
	}

	if (!IsObjectDistributed(address))
	{
		/* do not propagate alter types for non-distributed types */
		return false;
	}

	return true;
}