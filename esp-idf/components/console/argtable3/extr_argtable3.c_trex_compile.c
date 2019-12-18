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
typedef  int /*<<< orphan*/  jmp_buf ;
struct TYPE_9__ {char const* _p; int _nallocated; int _nsize; int _nsubexpr; size_t _first; char const** _error; int _flags; int /*<<< orphan*/ * _matches; TYPE_1__* _nodes; scalar_t__ _jmpbuf; int /*<<< orphan*/ * _bol; int /*<<< orphan*/  _eol; } ;
struct TYPE_8__ {int left; scalar_t__ type; int /*<<< orphan*/  next; int /*<<< orphan*/  right; } ;
typedef  TYPE_1__ TRexNode ;
typedef  int /*<<< orphan*/  TRexMatch ;
typedef  char TRexChar ;
typedef  TYPE_2__ TRex ;

/* Variables and functions */
 scalar_t__ MAX_CHAR ; 
 int /*<<< orphan*/  OP_EXPR ; 
 int /*<<< orphan*/  _SC (char*) ; 
 int /*<<< orphan*/ * g_nnames ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scprintf (int /*<<< orphan*/ ,...) ; 
 scalar_t__ scstrlen (char const*) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trex_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trex_free (TYPE_2__*) ; 
 int trex_list (TYPE_2__*) ; 
 size_t trex_newnode (TYPE_2__*,int /*<<< orphan*/ ) ; 

TRex *trex_compile(const TRexChar *pattern,const TRexChar **error,int flags)
{
	TRex *exp = (TRex *)malloc(sizeof(TRex));
	exp->_eol = exp->_bol = NULL;
	exp->_p = pattern;
	exp->_nallocated = (int)scstrlen(pattern) * sizeof(TRexChar);
	exp->_nodes = (TRexNode *)malloc(exp->_nallocated * sizeof(TRexNode));
	exp->_nsize = 0;
	exp->_matches = 0;
	exp->_nsubexpr = 0;
	exp->_first = trex_newnode(exp,OP_EXPR);
	exp->_error = error;
	exp->_jmpbuf = malloc(sizeof(jmp_buf));
	exp->_flags = flags;
	if(setjmp(*((jmp_buf*)exp->_jmpbuf)) == 0) {
		int res = trex_list(exp);
		exp->_nodes[exp->_first].left = res;
		if(*exp->_p!='\0')
			trex_error(exp,_SC("unexpected character"));
#ifdef _DEBUG
		{
			int nsize,i;
			TRexNode *t;
			nsize = exp->_nsize;
			t = &exp->_nodes[0];
			scprintf(_SC("\n"));
			for(i = 0;i < nsize; i++) {
				if(exp->_nodes[i].type>MAX_CHAR)
					scprintf(_SC("[%02d] %10s "),i,g_nnames[exp->_nodes[i].type-MAX_CHAR]);
				else
					scprintf(_SC("[%02d] %10c "),i,exp->_nodes[i].type);
				scprintf(_SC("left %02d right %02d next %02d\n"),exp->_nodes[i].left,exp->_nodes[i].right,exp->_nodes[i].next);
			}
			scprintf(_SC("\n"));
		}
#endif
		exp->_matches = (TRexMatch *) malloc(exp->_nsubexpr * sizeof(TRexMatch));
		memset(exp->_matches,0,exp->_nsubexpr * sizeof(TRexMatch));
	}
	else{
		trex_free(exp);
		return NULL;
	}
	return exp;
}