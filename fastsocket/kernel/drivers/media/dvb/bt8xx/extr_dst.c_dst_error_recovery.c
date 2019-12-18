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
struct dst_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_NOTICE ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  dst_pio_disable (struct dst_state*) ; 
 int /*<<< orphan*/  dst_pio_enable (struct dst_state*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  verbose ; 

int dst_error_recovery(struct dst_state *state)
{
	dprintk(verbose, DST_NOTICE, 1, "Trying to return from previous errors.");
	dst_pio_disable(state);
	msleep(10);
	dst_pio_enable(state);
	msleep(10);

	return 0;
}