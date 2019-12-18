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
struct mb86a16_state {int dummy; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int MB86A16_CRLFILTCOEF1 ; 
 int /*<<< orphan*/  MB86A16_ERROR ; 
 int MB86A16_FAGCS1 ; 
 int MB86A16_FAGCS2 ; 
 int MB86A16_FAGCS3 ; 
 int MB86A16_FAGCS4 ; 
 int MB86A16_FAGCS5 ; 
 int MB86A16_TSOUT ; 
 int MB86A16_VIMAG ; 
 scalar_t__ afcex_data_set (struct mb86a16_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ afcofs_data_set (struct mb86a16_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ mb86a16_write (struct mb86a16_state*,int,int) ; 
 scalar_t__ stlp_set (struct mb86a16_state*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int initial_set(struct mb86a16_state *state)
{
	if (stlp_set(state, 5, 7))
		goto err;

	udelay(100);
	if (afcex_data_set(state, 0, 0))
		goto err;

	udelay(100);
	if (afcofs_data_set(state, 0, 0))
		goto err;

	udelay(100);
	if (mb86a16_write(state, MB86A16_CRLFILTCOEF1, 0x16) < 0)
		goto err;
	if (mb86a16_write(state, 0x2f, 0x21) < 0)
		goto err;
	if (mb86a16_write(state, MB86A16_VIMAG, 0x38) < 0)
		goto err;
	if (mb86a16_write(state, MB86A16_FAGCS1, 0x00) < 0)
		goto err;
	if (mb86a16_write(state, MB86A16_FAGCS2, 0x1c) < 0)
		goto err;
	if (mb86a16_write(state, MB86A16_FAGCS3, 0x20) < 0)
		goto err;
	if (mb86a16_write(state, MB86A16_FAGCS4, 0x1e) < 0)
		goto err;
	if (mb86a16_write(state, MB86A16_FAGCS5, 0x23) < 0)
		goto err;
	if (mb86a16_write(state, 0x54, 0xff) < 0)
		goto err;
	if (mb86a16_write(state, MB86A16_TSOUT, 0x00) < 0)
		goto err;

	return 0;

err:
	dprintk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	return -EREMOTEIO;
}