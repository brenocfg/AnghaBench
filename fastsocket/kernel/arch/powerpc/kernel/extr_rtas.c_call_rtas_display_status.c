#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rtas_args {int token; int nargs; int nret; unsigned char* args; int /*<<< orphan*/ * rets; } ;
typedef  int /*<<< orphan*/  rtas_arg_t ;
struct TYPE_2__ {int /*<<< orphan*/  base; struct rtas_args args; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pa (struct rtas_args*) ; 
 int /*<<< orphan*/  enter_rtas (int /*<<< orphan*/ ) ; 
 unsigned long lock_rtas () ; 
 TYPE_1__ rtas ; 
 int /*<<< orphan*/  unlock_rtas (unsigned long) ; 

__attribute__((used)) static void call_rtas_display_status(char c)
{
	struct rtas_args *args = &rtas.args;
	unsigned long s;

	if (!rtas.base)
		return;
	s = lock_rtas();

	args->token = 10;
	args->nargs = 1;
	args->nret  = 1;
	args->rets  = (rtas_arg_t *)&(args->args[1]);
	args->args[0] = (unsigned char)c;

	enter_rtas(__pa(args));

	unlock_rtas(s);
}