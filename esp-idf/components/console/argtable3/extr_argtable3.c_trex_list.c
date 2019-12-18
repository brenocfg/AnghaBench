#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__* _p; TYPE_1__* _nodes; } ;
struct TYPE_6__ {int next; int left; int right; } ;
typedef  TYPE_2__ TRex ;

/* Variables and functions */
 int /*<<< orphan*/  OP_BOL ; 
 int /*<<< orphan*/  OP_OR ; 
 scalar_t__ TREX_SYMBOL_BEGINNING_OF_STRING ; 
 scalar_t__ TREX_SYMBOL_BRANCH ; 
 int trex_element (TYPE_2__*) ; 
 int trex_newnode (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trex_list(TRex *exp)
{
	int ret=-1,e;
	if(*exp->_p == TREX_SYMBOL_BEGINNING_OF_STRING) {
		exp->_p++;
		ret = trex_newnode(exp,OP_BOL);
	}
	e = trex_element(exp);
	if(ret != -1) {
		exp->_nodes[ret].next = e;
	}
	else ret = e;

	if(*exp->_p == TREX_SYMBOL_BRANCH) {
		int temp,tright;
		exp->_p++;
		temp = trex_newnode(exp,OP_OR);
		exp->_nodes[temp].left = ret;
		tright = trex_list(exp);
		exp->_nodes[temp].right = tright;
		ret = temp;
	}
	return ret;
}