#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  const* _eol; int /*<<< orphan*/  _nodes; scalar_t__ _currsubexp; int /*<<< orphan*/  const* _bol; } ;
typedef  int /*<<< orphan*/  TRexChar ;
typedef  int /*<<< orphan*/  TRexBool ;
typedef  TYPE_1__ TRex ;

/* Variables and functions */
 int /*<<< orphan*/  TRex_False ; 
 int /*<<< orphan*/  TRex_True ; 
 int scstrlen (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * trex_matchnode (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

TRexBool trex_match(TRex* exp,const TRexChar* text)
{
	const TRexChar* res = NULL;
	exp->_bol = text;
	exp->_eol = text + scstrlen(text);
	exp->_currsubexp = 0;
	res = trex_matchnode(exp,exp->_nodes,text,NULL);
	if(res == NULL || res != exp->_eol)
		return TRex_False;
	return TRex_True;
}