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
struct bttv {int i2c_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_I2C ; 
 int /*<<< orphan*/  btread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bttv_bit_setscl(void *data, int state)
{
	struct bttv *btv = (struct bttv*)data;

	if (state)
		btv->i2c_state |= 0x02;
	else
		btv->i2c_state &= ~0x02;
	btwrite(btv->i2c_state, BT848_I2C);
	btread(BT848_I2C);
}