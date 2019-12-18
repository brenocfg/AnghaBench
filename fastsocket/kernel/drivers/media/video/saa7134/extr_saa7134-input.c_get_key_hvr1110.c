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
typedef  unsigned char u32 ;
struct IR_i2c {int /*<<< orphan*/  c; } ;

/* Variables and functions */
 int EIO ; 
 int i2c_master_recv (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int get_key_hvr1110(struct IR_i2c *ir, u32 *ir_key, u32 *ir_raw)
{
	unsigned char buf[5], cod4, code3, code4;

	/* poll IR chip */
	if (5 != i2c_master_recv(ir->c, buf, 5))
		return -EIO;

	cod4	= buf[4];
	code4	= (cod4 >> 2);
	code3	= buf[3];
	if (code3 == 0)
		/* no key pressed */
		return 0;

	/* return key */
	*ir_key = code4;
	*ir_raw = code4;
	return 1;
}