#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rtas_args {scalar_t__ token; int nargs; int nret; scalar_t__* args; scalar_t__* rets; } ;

/* Variables and functions */
 scalar_t__ RTAS_UNKNOWN_SERVICE ; 
 scalar_t__ SURVEILLANCE_TOKEN ; 
 int /*<<< orphan*/  __pa (struct rtas_args*) ; 
 int /*<<< orphan*/  enter_rtas (int /*<<< orphan*/ ) ; 
 scalar_t__ rtas_token (char*) ; 

__attribute__((used)) static inline void disable_surveillance(void)
{
#ifdef CONFIG_PPC_PSERIES
	/* Since this can't be a module, args should end up below 4GB. */
	static struct rtas_args args;

	/*
	 * At this point we have got all the cpus we can into
	 * xmon, so there is hopefully no other cpu calling RTAS
	 * at the moment, even though we don't take rtas.lock.
	 * If we did try to take rtas.lock there would be a
	 * real possibility of deadlock.
	 */
	args.token = rtas_token("set-indicator");
	if (args.token == RTAS_UNKNOWN_SERVICE)
		return;
	args.nargs = 3;
	args.nret = 1;
	args.rets = &args.args[3];
	args.args[0] = SURVEILLANCE_TOKEN;
	args.args[1] = 0;
	args.args[2] = 0;
	enter_rtas(__pa(&args));
#endif /* CONFIG_PPC_PSERIES */
}