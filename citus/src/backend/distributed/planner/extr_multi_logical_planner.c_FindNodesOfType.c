#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * rightChildNode; int /*<<< orphan*/ * leftChildNode; } ;
struct TYPE_3__ {int /*<<< orphan*/ * childNode; } ;
typedef  TYPE_1__ MultiUnaryNode ;
typedef  int /*<<< orphan*/  MultiNode ;
typedef  TYPE_2__ MultiBinaryNode ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 scalar_t__ BinaryOperator (int /*<<< orphan*/ *) ; 
 int CitusNodeTag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 int T_Invalid ; 
 scalar_t__ UnaryOperator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

List *
FindNodesOfType(MultiNode *node, int type)
{
	List *nodeList = NIL;
	int nodeType = T_Invalid;

	/* terminal condition for recursion */
	if (node == NULL)
	{
		return NIL;
	}

	/* current node has expected node type */
	nodeType = CitusNodeTag(node);
	if (nodeType == type)
	{
		nodeList = lappend(nodeList, node);
	}

	if (UnaryOperator(node))
	{
		MultiNode *childNode = ((MultiUnaryNode *) node)->childNode;
		List *childNodeList = FindNodesOfType(childNode, type);

		nodeList = list_concat(nodeList, childNodeList);
	}
	else if (BinaryOperator(node))
	{
		MultiNode *leftChildNode = ((MultiBinaryNode *) node)->leftChildNode;
		MultiNode *rightChildNode = ((MultiBinaryNode *) node)->rightChildNode;

		List *leftChildNodeList = FindNodesOfType(leftChildNode, type);
		List *rightChildNodeList = FindNodesOfType(rightChildNode, type);

		nodeList = list_concat(nodeList, leftChildNodeList);
		nodeList = list_concat(nodeList, rightChildNodeList);
	}

	return nodeList;
}