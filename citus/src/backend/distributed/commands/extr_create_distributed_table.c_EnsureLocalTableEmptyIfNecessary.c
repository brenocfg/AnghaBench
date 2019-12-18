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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 char DISTRIBUTE_BY_HASH ; 
 char DISTRIBUTE_BY_NONE ; 
 int /*<<< orphan*/  EnsureLocalTableEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegularTable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
EnsureLocalTableEmptyIfNecessary(Oid relationId, char distributionMethod,
								 bool viaDepracatedAPI)
{
	if (viaDepracatedAPI)
	{
		EnsureLocalTableEmpty(relationId);
	}
	else if (distributionMethod != DISTRIBUTE_BY_HASH &&
			 distributionMethod != DISTRIBUTE_BY_NONE)
	{
		EnsureLocalTableEmpty(relationId);
	}
	else if (!RegularTable(relationId))
	{
		EnsureLocalTableEmpty(relationId);
	}
}