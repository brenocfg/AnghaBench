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
struct em28xx {int /*<<< orphan*/  i2c_client; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned char**) ; 
 int /*<<< orphan*/  i2c_master_send (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static int em28xx_initialize_mt9m111(struct em28xx *dev)
{
	int i;
	unsigned char regs[][3] = {
		{ 0x0d, 0x00, 0x01, },  /* reset and use defaults */
		{ 0x0d, 0x00, 0x00, },
		{ 0x0a, 0x00, 0x21, },
		{ 0x21, 0x04, 0x00, },  /* full readout speed, no row/col skipping */
	};

	for (i = 0; i < ARRAY_SIZE(regs); i++)
		i2c_master_send(&dev->i2c_client, &regs[i][0], 3);

	return 0;
}