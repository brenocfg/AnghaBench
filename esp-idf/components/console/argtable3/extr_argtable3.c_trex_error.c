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
typedef  int /*<<< orphan*/  jmp_buf ;
struct TYPE_3__ {scalar_t__ _jmpbuf; int /*<<< orphan*/  const** _error; } ;
typedef  int /*<<< orphan*/  TRexChar ;
typedef  TYPE_1__ TRex ;

/* Variables and functions */
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void trex_error(TRex *exp,const TRexChar *error)
{
	if(exp->_error) *exp->_error = error;
	longjmp(*((jmp_buf*)exp->_jmpbuf),-1);
}