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
struct TYPE_4__ {int* _p; } ;
typedef  char TRexChar ;
typedef  TYPE_1__ TRex ;

/* Variables and functions */
 int TREX_SYMBOL_ESCAPE_CHAR ; 
 int /*<<< orphan*/  _SC (char*) ; 
 int /*<<< orphan*/  scisprint (int) ; 
 int /*<<< orphan*/  trex_error (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TRexChar trex_escapechar(TRex *exp)
{
	if(*exp->_p == TREX_SYMBOL_ESCAPE_CHAR){
		exp->_p++;
		switch(*exp->_p) {
		case 'v': exp->_p++; return '\v';
		case 'n': exp->_p++; return '\n';
		case 't': exp->_p++; return '\t';
		case 'r': exp->_p++; return '\r';
		case 'f': exp->_p++; return '\f';
		default: return (*exp->_p++);
		}
	} else if(!scisprint((int) *exp->_p)) trex_error(exp,_SC("letter expected"));
	return (*exp->_p++);
}