#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int _nallocated; int _nsize; TYPE_1__* _nodes; int /*<<< orphan*/  _nsubexpr; } ;
struct TYPE_5__ {int next; int right; int left; scalar_t__ type; } ;
typedef  scalar_t__ TRexNodeType ;
typedef  TYPE_1__ TRexNode ;
typedef  TYPE_2__ TRex ;

/* Variables and functions */
 scalar_t__ OP_EXPR ; 
 scalar_t__ realloc (TYPE_1__*,int) ; 

__attribute__((used)) static int trex_newnode(TRex *exp, TRexNodeType type)
{
	TRexNode n;
	int newid;
	n.type = type;
	n.next = n.right = n.left = -1;
	if(type == OP_EXPR)
		n.right = exp->_nsubexpr++;
	if(exp->_nallocated < (exp->_nsize + 1)) {
		exp->_nallocated *= 2;
		exp->_nodes = (TRexNode *)realloc(exp->_nodes, exp->_nallocated * sizeof(TRexNode));
	}
	exp->_nodes[exp->_nsize++] = n;
	newid = exp->_nsize - 1;
	return (int)newid;
}