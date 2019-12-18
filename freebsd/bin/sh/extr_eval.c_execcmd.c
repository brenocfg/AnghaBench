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
struct TYPE_2__ {int count; int /*<<< orphan*/ * args; } ;

/* Variables and functions */
 int VEXPORT ; 
 int VSTACK ; 
 TYPE_1__* cmdenviron ; 
 int /*<<< orphan*/  environment () ; 
 scalar_t__ iflag ; 
 scalar_t__ mflag ; 
 int /*<<< orphan*/  optschanged () ; 
 int /*<<< orphan*/  pathval () ; 
 int /*<<< orphan*/  setvareq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  shellexec (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

int
execcmd(int argc, char **argv)
{
	int i;

	/*
	 * Because we have historically not supported any options,
	 * only treat "--" specially.
	 */
	if (argc > 1 && strcmp(argv[1], "--") == 0)
		argc--, argv++;
	if (argc > 1) {
		iflag = 0;		/* exit on error */
		mflag = 0;
		optschanged();
		for (i = 0; i < cmdenviron->count; i++)
			setvareq(cmdenviron->args[i], VEXPORT|VSTACK);
		shellexec(argv + 1, environment(), pathval(), 0);

	}
	return 0;
}