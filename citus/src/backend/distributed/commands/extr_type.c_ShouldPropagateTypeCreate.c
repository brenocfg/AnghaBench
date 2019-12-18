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
 int /*<<< orphan*/  EnableCreateTypePropagation ; 
 int /*<<< orphan*/  EnableDependencyCreation ; 
 scalar_t__ IsMultiStatementTransaction () ; 
 scalar_t__ creating_extension ; 

__attribute__((used)) static bool
ShouldPropagateTypeCreate()
{
	if (!EnableDependencyCreation)
	{
		/*
		 * we are configured to disable object propagation, should not propagate anything
		 */
		return false;
	}

	if (!EnableCreateTypePropagation)
	{
		/*
		 * Administrator has turned of type creation propagation
		 */
		return false;
	}

	if (creating_extension)
	{
		/*
		 * extensions should be created separately on the workers, types cascading from an
		 * extension should therefor not be propagated here.
		 */
		return false;
	}

	/*
	 * by not propagating in a transaction block we allow for parallelism to be used when
	 * this type will be used as a column in a table that will be created and distributed
	 * in this same transaction.
	 */
	if (IsMultiStatementTransaction())
	{
		return false;
	}

	return true;
}