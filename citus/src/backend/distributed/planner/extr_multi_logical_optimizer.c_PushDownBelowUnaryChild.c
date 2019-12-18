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

/* Variables and functions */
 int /*<<< orphan*/ * ChildNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ParentNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ParentSetNewChild (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetChild (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
PushDownBelowUnaryChild(MultiUnaryNode *currentNode, MultiUnaryNode *childNode)
{
	MultiNode *parentNode = ParentNode((MultiNode *) currentNode);
	MultiNode *childChildNode = ChildNode(childNode);

	/* current node's parent now points to the child node */
	ParentSetNewChild(parentNode, (MultiNode *) currentNode, (MultiNode *) childNode);

	/* current node's child becomes its parent */
	SetChild(childNode, (MultiNode *) currentNode);

	/* current node points to the child node's child */
	SetChild(currentNode, childChildNode);
}