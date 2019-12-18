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
typedef  int /*<<< orphan*/  u8 ;
struct stb0899_state {int /*<<< orphan*/  verbose; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  FIFOFULL ; 
 int /*<<< orphan*/  STB0899_DISSTATUS ; 
 int /*<<< orphan*/  STB0899_GETFIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  stb0899_read_reg (struct stb0899_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stb0899_wait_diseqc_fifo_empty(struct stb0899_state *state, int timeout)
{
	u8 reg = 0;
	unsigned long start = jiffies;

	while (1) {
		reg = stb0899_read_reg(state, STB0899_DISSTATUS);
		if (!STB0899_GETFIELD(FIFOFULL, reg))
			break;
		if ((jiffies - start) > timeout) {
			dprintk(state->verbose, FE_ERROR, 1, "timed out !!");
			return -ETIMEDOUT;
		}
	}

	return 0;
}