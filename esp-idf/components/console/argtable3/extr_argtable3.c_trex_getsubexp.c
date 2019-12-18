#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int _nsubexpr; int /*<<< orphan*/ * _matches; } ;
typedef  int /*<<< orphan*/  TRexMatch ;
typedef  int /*<<< orphan*/  TRexBool ;
typedef  TYPE_1__ TRex ;

/* Variables and functions */
 int /*<<< orphan*/  TRex_False ; 
 int /*<<< orphan*/  TRex_True ; 

TRexBool trex_getsubexp(TRex* exp, int n, TRexMatch *subexp)
{
	if( n<0 || n >= exp->_nsubexpr) return TRex_False;
	*subexp = exp->_matches[n];
	return TRex_True;
}