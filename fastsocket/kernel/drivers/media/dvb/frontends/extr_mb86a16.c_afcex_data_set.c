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
 int /*<<< orphan*/  MB86A16_AFCEXH ; 
 int /*<<< orphan*/  MB86A16_AFCEXL ; 
 int /*<<< orphan*/  MB86A16_ERROR ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ mb86a16_write (struct mb86a16_state*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int afcex_data_set(struct mb86a16_state *state,
			  unsigned char AFCEX_L,
			  unsigned char AFCEX_H)
{
	if (mb86a16_write(state, MB86A16_AFCEXL, AFCEX_L) < 0)
		goto err;
	if (mb86a16_write(state, MB86A16_AFCEXH, AFCEX_H) < 0)
		goto err;

	return 0;
err:
	dprintk(verbose, MB86A16_ERROR, 1, "I2C transfer error");

	return -1;
}