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
typedef  TYPE_1__ TRex ;

/* Variables and functions */
 int /*<<< orphan*/  _SC (char*) ; 
 int /*<<< orphan*/  trex_error (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void trex_expect(TRex *exp, int n){
	if((*exp->_p) != n)
		trex_error(exp, _SC("expected paren"));
	exp->_p++;
}