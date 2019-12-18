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
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
RemoveUnaryNode(MultiUnaryNode *unaryNode)
{
	MultiNode *parentNode = ParentNode((MultiNode *) unaryNode);
	MultiNode *childNode = ChildNode(unaryNode);

	/* set parent to directly point to unary node's child */
	ParentSetNewChild(parentNode, (MultiNode *) unaryNode, childNode);

	pfree(unaryNode);
}