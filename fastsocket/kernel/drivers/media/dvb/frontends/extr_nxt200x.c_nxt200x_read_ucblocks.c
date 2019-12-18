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
typedef  int /*<<< orphan*/  u32 ;
struct nxt200x_state {int dummy; } ;
struct dvb_frontend {struct nxt200x_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  nxt200x_readreg_multibyte (struct nxt200x_state*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int nxt200x_read_ucblocks(struct dvb_frontend* fe, u32* ucblocks)
{
	struct nxt200x_state* state = fe->demodulator_priv;
	u8 b[3];

	nxt200x_readreg_multibyte(state, 0xE6, b, 3);
	*ucblocks = b[2];

	return 0;
}