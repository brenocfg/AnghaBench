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
typedef  int u32 ;
typedef  int u16 ;
struct IR_i2c {unsigned char old; int /*<<< orphan*/  c; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EIO ; 
 int i2c_master_recv (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  i2cdprintk (char*,int,unsigned char,unsigned char) ; 

int em28xx_get_key_em_haup(struct IR_i2c *ir, u32 *ir_key, u32 *ir_raw)
{
	unsigned char buf[2];
	u16 code;
	int size;

	/* poll IR chip */
	size = i2c_master_recv(ir->c, buf, sizeof(buf));

	if (size != 2)
		return -EIO;

	/* Does eliminate repeated parity code */
	if (buf[1] == 0xff)
		return 0;

	ir->old = buf[1];

	/*
	 * Rearranges bits to the right order.
	 * The bit order were determined experimentally by using
	 * The original Hauppauge Grey IR and another RC5 that uses addr=0x08
	 * The RC5 code has 14 bits, but we've experimentally determined
	 * the meaning for only 11 bits.
	 * So, the code translation is not complete. Yet, it is enough to
	 * work with the provided RC5 IR.
	 */
	code =
		 ((buf[0] & 0x01) ? 0x0020 : 0) | /* 		0010 0000 */
		 ((buf[0] & 0x02) ? 0x0010 : 0) | /* 		0001 0000 */
		 ((buf[0] & 0x04) ? 0x0008 : 0) | /* 		0000 1000 */
		 ((buf[0] & 0x08) ? 0x0004 : 0) | /* 		0000 0100 */
		 ((buf[0] & 0x10) ? 0x0002 : 0) | /* 		0000 0010 */
		 ((buf[0] & 0x20) ? 0x0001 : 0) | /* 		0000 0001 */
		 ((buf[1] & 0x08) ? 0x1000 : 0) | /* 0001 0000		  */
		 ((buf[1] & 0x10) ? 0x0800 : 0) | /* 0000 1000		  */
		 ((buf[1] & 0x20) ? 0x0400 : 0) | /* 0000 0100		  */
		 ((buf[1] & 0x40) ? 0x0200 : 0) | /* 0000 0010		  */
		 ((buf[1] & 0x80) ? 0x0100 : 0);  /* 0000 0001		  */

	i2cdprintk("ir hauppauge (em2840): code=0x%02x (rcv=0x%02x%02x)\n",
			code, buf[1], buf[0]);

	/* return key */
	*ir_key = code;
	*ir_raw = code;
	return 1;
}