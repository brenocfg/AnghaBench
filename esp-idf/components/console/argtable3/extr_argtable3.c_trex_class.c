#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* _p; char* _eol; TYPE_1__* _nodes; } ;
struct TYPE_8__ {scalar_t__ type; int left; int right; int next; } ;
typedef  TYPE_2__ TRex ;

/* Variables and functions */
 scalar_t__ OP_CCLASS ; 
 int /*<<< orphan*/  OP_CLASS ; 
 int /*<<< orphan*/  OP_NCLASS ; 
 int /*<<< orphan*/  OP_RANGE ; 
 char TREX_SYMBOL_BEGINNING_OF_STRING ; 
 int /*<<< orphan*/  TRex_True ; 
 int /*<<< orphan*/  _SC (char*) ; 
 int trex_charnode (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trex_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int trex_escapechar (TYPE_2__*) ; 
 int trex_newnode (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trex_class(TRex *exp)
{
	int ret = -1;
	int first = -1,chain;
	if(*exp->_p == TREX_SYMBOL_BEGINNING_OF_STRING){
		ret = trex_newnode(exp,OP_NCLASS);
		exp->_p++;
	}else ret = trex_newnode(exp,OP_CLASS);

	if(*exp->_p == ']') trex_error(exp,_SC("empty class"));
	chain = ret;
	while(*exp->_p != ']' && exp->_p != exp->_eol) {
		if(*exp->_p == '-' && first != -1){
			int r,t;
			if(*exp->_p++ == ']') trex_error(exp,_SC("unfinished range"));
			r = trex_newnode(exp,OP_RANGE);
			if(first>*exp->_p) trex_error(exp,_SC("invalid range"));
			if(exp->_nodes[first].type == OP_CCLASS) trex_error(exp,_SC("cannot use character classes in ranges"));
			exp->_nodes[r].left = exp->_nodes[first].type;
			t = trex_escapechar(exp);
			exp->_nodes[r].right = t;
            exp->_nodes[chain].next = r;
			chain = r;
			first = -1;
		}
		else{
			if(first!=-1){
				int c = first;
				exp->_nodes[chain].next = c;
				chain = c;
				first = trex_charnode(exp,TRex_True);
			}
			else{
				first = trex_charnode(exp,TRex_True);
			}
		}
	}
	if(first!=-1){
		int c = first;
		exp->_nodes[chain].next = c;
		chain = c;
		first = -1;
	}
	/* hack? */
	exp->_nodes[ret].left = exp->_nodes[ret].next;
	exp->_nodes[ret].next = -1;
	return ret;
}