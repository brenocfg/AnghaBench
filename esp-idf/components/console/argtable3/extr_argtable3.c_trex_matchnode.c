#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int const* _eol; int _currsubexp; int const* _bol; int _flags; TYPE_2__* _nodes; TYPE_1__* _matches; } ;
struct TYPE_10__ {int type; int right; int next; size_t left; } ;
struct TYPE_9__ {int const* begin; int const* len; } ;
typedef  int TRexNodeType ;
typedef  TYPE_2__ TRexNode ;
typedef  int TRexChar ;
typedef  TYPE_3__ TRex ;

/* Variables and functions */
#define  OP_BOL 138 
#define  OP_CCLASS 137 
#define  OP_CLASS 136 
#define  OP_DOT 135 
#define  OP_EOL 134 
#define  OP_EXPR 133 
#define  OP_GREEDY 132 
#define  OP_NCLASS 131 
#define  OP_NOCAPEXPR 130 
#define  OP_OR 129 
#define  OP_WB 128 
 int TREX_ICASE ; 
 int /*<<< orphan*/  TRex_False ; 
 int /*<<< orphan*/  TRex_True ; 
 int /*<<< orphan*/  isspace (int) ; 
 int const tolower (int const) ; 
 int const toupper (int const) ; 
 int /*<<< orphan*/  trex_matchcclass (size_t,int const) ; 
 int /*<<< orphan*/  trex_matchclass (TYPE_3__*,TYPE_2__*,int const) ; 

__attribute__((used)) static const TRexChar *trex_matchnode(TRex* exp,TRexNode *node,const TRexChar *str,TRexNode *next)
{

	TRexNodeType type = node->type;
	switch(type) {
	case OP_GREEDY: {
		//TRexNode *greedystop = (node->next != -1) ? &exp->_nodes[node->next] : NULL;
		TRexNode *greedystop = NULL;
		int p0 = (node->right >> 16)&0x0000FFFF, p1 = node->right&0x0000FFFF, nmaches = 0;
		const TRexChar *s=str, *good = str;

		if(node->next != -1) {
			greedystop = &exp->_nodes[node->next];
		}
		else {
			greedystop = next;
		}

		while((nmaches == 0xFFFF || nmaches < p1)) {

			const TRexChar *stop;
			if(!(s = trex_matchnode(exp,&exp->_nodes[node->left],s,greedystop)))
				break;
			nmaches++;
			good=s;
			if(greedystop) {
				//checks that 0 matches satisfy the expression(if so skips)
				//if not would always stop(for instance if is a '?')
				if(greedystop->type != OP_GREEDY ||
				(greedystop->type == OP_GREEDY && ((greedystop->right >> 16)&0x0000FFFF) != 0))
				{
					TRexNode *gnext = NULL;
					if(greedystop->next != -1) {
						gnext = &exp->_nodes[greedystop->next];
					}else if(next && next->next != -1){
						gnext = &exp->_nodes[next->next];
					}
					stop = trex_matchnode(exp,greedystop,s,gnext);
					if(stop) {
						//if satisfied stop it
						if(p0 == p1 && p0 == nmaches) break;
						else if(nmaches >= p0 && p1 == 0xFFFF) break;
						else if(nmaches >= p0 && nmaches <= p1) break;
					}
				}
			}

			if(s >= exp->_eol)
				break;
		}
		if(p0 == p1 && p0 == nmaches) return good;
		else if(nmaches >= p0 && p1 == 0xFFFF) return good;
		else if(nmaches >= p0 && nmaches <= p1) return good;
		return NULL;
	}
	case OP_OR: {
			const TRexChar *asd = str;
			TRexNode *temp=&exp->_nodes[node->left];
			while( (asd = trex_matchnode(exp,temp,asd,NULL)) ) {
				if(temp->next != -1)
					temp = &exp->_nodes[temp->next];
				else
					return asd;
			}
			asd = str;
			temp = &exp->_nodes[node->right];
			while( (asd = trex_matchnode(exp,temp,asd,NULL)) ) {
				if(temp->next != -1)
					temp = &exp->_nodes[temp->next];
				else
					return asd;
			}
			return NULL;
			break;
	}
	case OP_EXPR:
	case OP_NOCAPEXPR:{
			TRexNode *n = &exp->_nodes[node->left];
			const TRexChar *cur = str;
			int capture = -1;
			if(node->type != OP_NOCAPEXPR && node->right == exp->_currsubexp) {
				capture = exp->_currsubexp;
				exp->_matches[capture].begin = cur;
				exp->_currsubexp++;
			}

			do {
				TRexNode *subnext = NULL;
				if(n->next != -1) {
					subnext = &exp->_nodes[n->next];
				}else {
					subnext = next;
				}
				if(!(cur = trex_matchnode(exp,n,cur,subnext))) {
					if(capture != -1){
						exp->_matches[capture].begin = 0;
						exp->_matches[capture].len = 0;
					}
					return NULL;
				}
			} while((n->next != -1) && (n = &exp->_nodes[n->next]));

			if(capture != -1)
				exp->_matches[capture].len = cur - exp->_matches[capture].begin;
			return cur;
	}
	case OP_WB:
		if((str == exp->_bol && !isspace((int) *str))
		 || ((str == exp->_eol && !isspace((int) *(str-1))))
		 || ((!isspace((int) *str) && isspace((int) *(str+1))))
		 || ((isspace((int) *str) && !isspace((int) *(str+1)))) ) {
			return (node->left == 'b')?str:NULL;
		}
		return (node->left == 'b')?NULL:str;
	case OP_BOL:
		if(str == exp->_bol) return str;
		return NULL;
	case OP_EOL:
		if(str == exp->_eol) return str;
		return NULL;
	case OP_DOT:
		str++;
		return str;
	case OP_NCLASS:
	case OP_CLASS:
		if(trex_matchclass(exp,&exp->_nodes[node->left],*str)?(type == OP_CLASS?TRex_True:TRex_False):(type == OP_NCLASS?TRex_True:TRex_False)) {
                        str++;
			return str;
		}
		return NULL;
	case OP_CCLASS:
		if(trex_matchcclass(node->left,*str)) {
                        str++;
			return str;
		}
		return NULL;
	default: /* char */
		if (exp->_flags & TREX_ICASE)
		{
			if(*str != tolower(node->type) && *str != toupper(node->type)) return NULL;
		}
		else
		{
			if (*str != node->type) return NULL;
		}
		str++;
		return str;
	}
	return NULL;
}