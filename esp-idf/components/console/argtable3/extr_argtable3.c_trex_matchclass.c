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
struct TYPE_6__ {int _flags; TYPE_1__* _nodes; } ;
struct TYPE_5__ {int next; int type; int left; int right; } ;
typedef  TYPE_1__ TRexNode ;
typedef  int TRexChar ;
typedef  int /*<<< orphan*/  TRexBool ;
typedef  TYPE_2__ TRex ;

/* Variables and functions */
#define  OP_CCLASS 129 
#define  OP_RANGE 128 
 int TREX_ICASE ; 
 int /*<<< orphan*/  TRex_False ; 
 int /*<<< orphan*/  TRex_True ; 
 int tolower (int) ; 
 int toupper (int) ; 
 int /*<<< orphan*/  trex_matchcclass (int,int) ; 

__attribute__((used)) static TRexBool trex_matchclass(TRex* exp,TRexNode *node,TRexChar c)
{
	do {
		switch(node->type) {
			case OP_RANGE:
				if (exp->_flags & TREX_ICASE)
				{
					if(c >= toupper(node->left) && c <= toupper(node->right)) return TRex_True;
					if(c >= tolower(node->left) && c <= tolower(node->right)) return TRex_True;
				}
				else
				{
					if(c >= node->left && c <= node->right) return TRex_True;
				}
				break;
			case OP_CCLASS:
				if(trex_matchcclass(node->left,c)) return TRex_True;
				break;
			default:
				if (exp->_flags & TREX_ICASE)
				{
					if (c == tolower(node->type) || c == toupper(node->type)) return TRex_True;
				}
				else
				{
					if(c == node->type)return TRex_True;
				}

		}
	} while((node->next != -1) && (node = &exp->_nodes[node->next]));
	return TRex_False;
}