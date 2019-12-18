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
 int /*<<< orphan*/  MB86A16_ERROR ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ mb86a16_write (struct mb86a16_state*,int,int) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int rf_val_set(struct mb86a16_state *state,
		      int f,
		      int smrt,
		      unsigned char R)
{
	unsigned char C, F, B;
	int M;
	unsigned char rf_val[5];
	int ack = -1;

	if (smrt > 37750)
		C = 1;
	else if (smrt > 18875)
		C = 2;
	else if (smrt > 5500)
		C = 3;
	else
		C = 4;

	if (smrt > 30500)
		F = 3;
	else if (smrt > 9375)
		F = 1;
	else if (smrt > 4625)
		F = 0;
	else
		F = 2;

	if (f < 1060)
		B = 0;
	else if (f < 1175)
		B = 1;
	else if (f < 1305)
		B = 2;
	else if (f < 1435)
		B = 3;
	else if (f < 1570)
		B = 4;
	else if (f < 1715)
		B = 5;
	else if (f < 1845)
		B = 6;
	else if (f < 1980)
		B = 7;
	else if (f < 2080)
		B = 8;
	else
		B = 9;

	M = f * (1 << R) / 2;

	rf_val[0] = 0x01 | (C << 3) | (F << 1);
	rf_val[1] = (R << 5) | ((M & 0x1f000) >> 12);
	rf_val[2] = (M & 0x00ff0) >> 4;
	rf_val[3] = ((M & 0x0000f) << 4) | B;

	/* Frequency Set */
	if (mb86a16_write(state, 0x21, rf_val[0]) < 0)
		ack = 0;
	if (mb86a16_write(state, 0x22, rf_val[1]) < 0)
		ack = 0;
	if (mb86a16_write(state, 0x23, rf_val[2]) < 0)
		ack = 0;
	if (mb86a16_write(state, 0x24, rf_val[3]) < 0)
		ack = 0;
	if (mb86a16_write(state, 0x25, 0x01) < 0)
		ack = 0;
	if (ack == 0) {
		dprintk(verbose, MB86A16_ERROR, 1, "RF Setup - I2C transfer error");
		return -EREMOTEIO;
	}

	return 0;
}