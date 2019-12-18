#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ff_gameid; int ff_partysize; int ff_hassummons; } ;
typedef  TYPE_1__ final_fantasy_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  ff_getgameid (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_getpartysize (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_getsummons (TYPE_1__*) ; 
 int /*<<< orphan*/  sleep (int) ; 

int
main(void)
{
	final_fantasy_info_t ffiii, ffx, ffi;

	ffi.ff_gameid = 1;
	ffi.ff_partysize = 4;
	ffi.ff_hassummons = 0;

	ffiii.ff_gameid = 6;
	ffiii.ff_partysize = 4;
	ffiii.ff_hassummons = 1;

	ffx.ff_gameid = 10;
	ffx.ff_partysize = 3;
	ffx.ff_hassummons = 1;

	for (;;) {
		ff_getgameid(&ffi);
		ff_getpartysize(&ffx);
		ff_getsummons(&ffiii);
		sleep(1);
	}
	/*NOTREACHED*/
	return (0);
}