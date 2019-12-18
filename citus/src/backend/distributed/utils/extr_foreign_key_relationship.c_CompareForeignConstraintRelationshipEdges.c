#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int referencingRelationOID; int referencedRelationOID; } ;
typedef  TYPE_1__ ForeignConstraintRelationshipEdge ;

/* Variables and functions */

__attribute__((used)) static int
CompareForeignConstraintRelationshipEdges(const void *leftElement, const
										  void *rightElement)
{
	const ForeignConstraintRelationshipEdge *leftEdge = *((const
														   ForeignConstraintRelationshipEdge
														   **) leftElement);
	const ForeignConstraintRelationshipEdge *rightEdge = *((const
															ForeignConstraintRelationshipEdge
															**) rightElement);

	int referencingDiff = leftEdge->referencingRelationOID -
						  rightEdge->referencingRelationOID;
	int referencedDiff = leftEdge->referencedRelationOID -
						 rightEdge->referencedRelationOID;

	if (referencingDiff != 0)
	{
		return referencingDiff;
	}

	return referencedDiff;
}