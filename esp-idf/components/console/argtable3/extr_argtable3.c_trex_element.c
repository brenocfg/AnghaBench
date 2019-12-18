#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int* _p; TYPE_1__* _nodes; } ;
struct TYPE_11__ {int left; unsigned short right; int next; } ;
typedef  scalar_t__ TRexBool ;
typedef  TYPE_2__ TRex ;

/* Variables and functions */
 int /*<<< orphan*/  OP_DOT ; 
 int /*<<< orphan*/  OP_EOL ; 
 int /*<<< orphan*/  OP_EXPR ; 
 int /*<<< orphan*/  OP_GREEDY ; 
 int /*<<< orphan*/  OP_NOCAPEXPR ; 
#define  TREX_SYMBOL_ANY_CHAR 132 
 int TREX_SYMBOL_BRANCH ; 
#define  TREX_SYMBOL_END_OF_STRING 131 
#define  TREX_SYMBOL_GREEDY_ONE_OR_MORE 130 
#define  TREX_SYMBOL_GREEDY_ZERO_OR_MORE 129 
#define  TREX_SYMBOL_GREEDY_ZERO_OR_ONE 128 
 scalar_t__ TRex_False ; 
 scalar_t__ TRex_True ; 
 int /*<<< orphan*/  _SC (char*) ; 
 int /*<<< orphan*/  isdigit (int) ; 
 int trex_charnode (TYPE_2__*,scalar_t__) ; 
 int trex_class (TYPE_2__*) ; 
 int /*<<< orphan*/  trex_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trex_expect (TYPE_2__*,char) ; 
 int trex_list (TYPE_2__*) ; 
 int trex_newnode (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ trex_parsenumber (TYPE_2__*) ; 

__attribute__((used)) static int trex_element(TRex *exp)
{
	int ret = -1;
	switch(*exp->_p)
	{
	case '(': {
		int expr,newn;
		exp->_p++;


		if(*exp->_p =='?') {
			exp->_p++;
			trex_expect(exp,':');
			expr = trex_newnode(exp,OP_NOCAPEXPR);
		}
		else
			expr = trex_newnode(exp,OP_EXPR);
		newn = trex_list(exp);
		exp->_nodes[expr].left = newn;
		ret = expr;
		trex_expect(exp,')');
			  }
			  break;
	case '[':
		exp->_p++;
		ret = trex_class(exp);
		trex_expect(exp,']');
		break;
	case TREX_SYMBOL_END_OF_STRING: exp->_p++; ret = trex_newnode(exp,OP_EOL);break;
	case TREX_SYMBOL_ANY_CHAR: exp->_p++; ret = trex_newnode(exp,OP_DOT);break;
	default:
		ret = trex_charnode(exp,TRex_False);
		break;
	}

	{
		TRexBool isgreedy = TRex_False;
		unsigned short p0 = 0, p1 = 0;
		switch(*exp->_p){
			case TREX_SYMBOL_GREEDY_ZERO_OR_MORE: p0 = 0; p1 = 0xFFFF; exp->_p++; isgreedy = TRex_True; break;
			case TREX_SYMBOL_GREEDY_ONE_OR_MORE: p0 = 1; p1 = 0xFFFF; exp->_p++; isgreedy = TRex_True; break;
			case TREX_SYMBOL_GREEDY_ZERO_OR_ONE: p0 = 0; p1 = 1; exp->_p++; isgreedy = TRex_True; break;
			case '{':
				exp->_p++;
				if(!isdigit((int) *exp->_p)) trex_error(exp,_SC("number expected"));
				p0 = (unsigned short)trex_parsenumber(exp);
				/*******************************/
				switch(*exp->_p) {
			case '}':
				p1 = p0; exp->_p++;
				break;
			case ',':
				exp->_p++;
				p1 = 0xFFFF;
				if(isdigit((int) *exp->_p)){
					p1 = (unsigned short)trex_parsenumber(exp);
				}
				trex_expect(exp,'}');
				break;
			default:
				trex_error(exp,_SC(", or } expected"));
		}
		/*******************************/
		isgreedy = TRex_True;
		break;

		}
		if(isgreedy) {
			int nnode = trex_newnode(exp,OP_GREEDY);
			exp->_nodes[nnode].left = ret;
			exp->_nodes[nnode].right = ((p0)<<16)|p1;
			ret = nnode;
		}
	}
	if((*exp->_p != TREX_SYMBOL_BRANCH) && (*exp->_p != ')') && (*exp->_p != TREX_SYMBOL_GREEDY_ZERO_OR_MORE) && (*exp->_p != TREX_SYMBOL_GREEDY_ONE_OR_MORE) && (*exp->_p != '\0')) {
		int nnode = trex_element(exp);
		exp->_nodes[ret].next = nnode;
	}

	return ret;
}