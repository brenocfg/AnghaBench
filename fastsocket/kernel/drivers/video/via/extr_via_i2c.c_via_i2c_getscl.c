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
struct via_i2c_stuff {int /*<<< orphan*/  i2c_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIASR ; 
 int viafb_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int via_i2c_getscl(void *data)
{
	struct via_i2c_stuff *via_i2c_chan = (struct via_i2c_stuff *)data;

	if (viafb_read_reg(VIASR, via_i2c_chan->i2c_port) & 0x08)
		return 1;
	return 0;
}