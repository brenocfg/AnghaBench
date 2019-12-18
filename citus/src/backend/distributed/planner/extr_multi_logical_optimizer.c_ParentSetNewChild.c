#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * leftChildNode; } ;
typedef  int /*<<< orphan*/  MultiUnaryNode ;
typedef  int /*<<< orphan*/  MultiNode ;
typedef  TYPE_1__ MultiBinaryNode ;

/* Variables and functions */
 int BinaryOperator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetChild (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLeftChild (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetRightChild (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int UnaryOperator (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ParentSetNewChild(MultiNode *parentNode, MultiNode *oldChildNode,
				  MultiNode *newChildNode)
{
	bool unaryParent = UnaryOperator(parentNode);
	bool binaryParent = BinaryOperator(parentNode);

	if (unaryParent)
	{
		MultiUnaryNode *unaryParentNode = (MultiUnaryNode *) parentNode;
		SetChild(unaryParentNode, newChildNode);
	}
	else if (binaryParent)
	{
		MultiBinaryNode *binaryParentNode = (MultiBinaryNode *) parentNode;

		/* determine which side of the parent the old child is on */
		if (binaryParentNode->leftChildNode == oldChildNode)
		{
			SetLeftChild(binaryParentNode, newChildNode);
		}
		else
		{
			SetRightChild(binaryParentNode, newChildNode);
		}
	}
}