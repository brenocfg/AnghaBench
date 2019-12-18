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
struct rubin_state {int rec_q; int /*<<< orphan*/  pp; scalar_t__ bit_number; } ;

/* Variables and functions */
 scalar_t__ RUBIN_REG_SIZE ; 
 int /*<<< orphan*/  init_rubin (struct rubin_state*,int,int*) ; 
 scalar_t__ pullbit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_decode(struct rubin_state *rs, int div, int *bits)
{
	init_rubin(rs, div, bits);

	/* behalve lower */
	rs->rec_q = 0;

	for (rs->bit_number = 0; rs->bit_number++ < RUBIN_REG_SIZE;
	     rs->rec_q = rs->rec_q * 2 + (long) (pullbit(&rs->pp)))
		;
}