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
struct rubin_state {int q; int /*<<< orphan*/  pp; } ;

/* Variables and functions */
 int LOWER_BITS_RUBIN ; 
 int RUBIN_REG_SIZE ; 
 int UPPER_BIT_RUBIN ; 
 int /*<<< orphan*/  pushbit (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void end_rubin(struct rubin_state *rs)
{

	int i;

	for (i = 0; i < RUBIN_REG_SIZE; i++) {
		pushbit(&rs->pp, (UPPER_BIT_RUBIN & rs->q) ? 1 : 0, 1);
		rs->q &= LOWER_BITS_RUBIN;
		rs->q <<= 1;
	}
}