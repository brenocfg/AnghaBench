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
typedef  int /*<<< orphan*/  MultiUnaryNode ;
typedef  int /*<<< orphan*/  MultiNode ;
typedef  int /*<<< orphan*/  MultiExtendedOp ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ChildNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CitusIsA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MultiCollect ; 
 int /*<<< orphan*/ * ParentNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetChild (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnaryOperator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ApplyExtendedOpNodes(MultiExtendedOp *originalNode, MultiExtendedOp *masterNode,
					 MultiExtendedOp *workerNode)
{
	MultiNode *parentNode = ParentNode((MultiNode *) originalNode);
	MultiNode *collectNode = ChildNode((MultiUnaryNode *) originalNode);
	MultiNode *collectChildNode = ChildNode((MultiUnaryNode *) collectNode);

	/* original node's child must be a collect node */
	Assert(CitusIsA(collectNode, MultiCollect));
	Assert(UnaryOperator(parentNode));

	/* swap the original aggregate node with the master extended node */
	SetChild((MultiUnaryNode *) parentNode, (MultiNode *) masterNode);
	SetChild((MultiUnaryNode *) masterNode, (MultiNode *) collectNode);

	/* add the worker extended node below the collect node */
	SetChild((MultiUnaryNode *) collectNode, (MultiNode *) workerNode);
	SetChild((MultiUnaryNode *) workerNode, (MultiNode *) collectChildNode);

	/* clean up the original extended operator node */
	pfree(originalNode);
}