#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * leftChildNode; } ;
struct TYPE_9__ {int /*<<< orphan*/ * childNode; } ;
typedef  TYPE_1__ MultiUnaryNode ;
typedef  int /*<<< orphan*/  MultiNode ;
typedef  TYPE_2__ MultiBinaryNode ;

/* Variables and functions */
 int BinaryOperator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ParentNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ParentSetNewChild (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PushDownBelowUnaryChild (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  SetChild (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLeftChild (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetRightChild (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int UnaryOperator (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
PullUpUnaryNode(MultiUnaryNode *unaryNode)
{
	MultiNode *parentNode = ParentNode((MultiNode *) unaryNode);
	bool unaryParent = UnaryOperator(parentNode);
	bool binaryParent = BinaryOperator(parentNode);

	if (unaryParent)
	{
		/* pulling up a node is the same as pushing down the node's unary parent */
		MultiUnaryNode *unaryParentNode = (MultiUnaryNode *) parentNode;
		PushDownBelowUnaryChild(unaryParentNode, unaryNode);
	}
	else if (binaryParent)
	{
		MultiBinaryNode *binaryParentNode = (MultiBinaryNode *) parentNode;
		MultiNode *parentParentNode = ParentNode((MultiNode *) binaryParentNode);
		MultiNode *childNode = unaryNode->childNode;

		/* make the parent node point to the unary node's child node */
		if (binaryParentNode->leftChildNode == ((MultiNode *) unaryNode))
		{
			SetLeftChild(binaryParentNode, childNode);
		}
		else
		{
			SetRightChild(binaryParentNode, childNode);
		}

		/* make the parent parent node point to the unary node */
		ParentSetNewChild(parentParentNode, parentNode, (MultiNode *) unaryNode);

		/* make the unary node point to the (old) parent node */
		SetChild(unaryNode, parentNode);
	}
}