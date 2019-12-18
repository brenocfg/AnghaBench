#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  nodeMap; } ;
struct TYPE_5__ {void* backAdjacencyList; void* adjacencyList; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ForeignConstraintRelationshipNode ;

/* Variables and functions */
 TYPE_1__* CreateOrFindNode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* fConstraintRelationshipGraph ; 
 void* lappend (void*,TYPE_1__*) ; 

__attribute__((used)) static void
AddForeignConstraintRelationshipEdge(Oid referencingOid, Oid referencedOid)
{
	ForeignConstraintRelationshipNode *referencingNode = CreateOrFindNode(
		fConstraintRelationshipGraph->nodeMap, referencingOid);
	ForeignConstraintRelationshipNode *referencedNode = CreateOrFindNode(
		fConstraintRelationshipGraph->nodeMap, referencedOid);

	referencingNode->adjacencyList = lappend(referencingNode->adjacencyList,
											 referencedNode);
	referencedNode->backAdjacencyList = lappend(referencedNode->backAdjacencyList,
												referencingNode);
}