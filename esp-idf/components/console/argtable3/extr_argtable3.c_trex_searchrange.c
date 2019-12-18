#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int next; } ;
struct TYPE_5__ {int _first; TYPE_4__* _nodes; scalar_t__ _currsubexp; int /*<<< orphan*/  const* _eol; int /*<<< orphan*/  const* _bol; } ;
typedef  int /*<<< orphan*/  TRexChar ;
typedef  int /*<<< orphan*/  TRexBool ;
typedef  TYPE_1__ TRex ;

/* Variables and functions */
 int /*<<< orphan*/  TRex_False ; 
 int /*<<< orphan*/  TRex_True ; 
 int /*<<< orphan*/ * trex_matchnode (TYPE_1__*,TYPE_4__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

TRexBool trex_searchrange(TRex* exp,const TRexChar* text_begin,const TRexChar* text_end,const TRexChar** out_begin, const TRexChar** out_end)
{
	const TRexChar *cur = NULL;
	int node = exp->_first;
	if(text_begin >= text_end) return TRex_False;
	exp->_bol = text_begin;
	exp->_eol = text_end;
	do {
		cur = text_begin;
		while(node != -1) {
			exp->_currsubexp = 0;
			cur = trex_matchnode(exp,&exp->_nodes[node],cur,NULL);
			if(!cur)
				break;
			node = exp->_nodes[node].next;
		}
		text_begin++;
	} while(cur == NULL && text_begin != text_end);

	if(cur == NULL)
		return TRex_False;

	--text_begin;

	if(out_begin) *out_begin = text_begin;
	if(out_end) *out_end = cur;
	return TRex_True;
}