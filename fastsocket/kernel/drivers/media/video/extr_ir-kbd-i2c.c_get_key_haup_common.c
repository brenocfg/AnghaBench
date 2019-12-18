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
struct IR_i2c {int /*<<< orphan*/  c; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dprintk (int,char*,int,int,int,int,int) ; 
 int i2c_master_recv (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int get_key_haup_common(struct IR_i2c *ir, u32 *ir_key, u32 *ir_raw,
			       int size, int offset)
{
	unsigned char buf[6];
	int start, range, toggle, dev, code, ircode;

	/* poll IR chip */
	if (size != i2c_master_recv(ir->c, buf, size))
		return -EIO;

	/* split rc5 data block ... */
	start  = (buf[offset] >> 7) &    1;
	range  = (buf[offset] >> 6) &    1;
	toggle = (buf[offset] >> 5) &    1;
	dev    =  buf[offset]       & 0x1f;
	code   = (buf[offset+1] >> 2) & 0x3f;

	/* rc5 has two start bits
	 * the first bit must be one
	 * the second bit defines the command range (1 = 0-63, 0 = 64 - 127)
	 */
	if (!start)
		/* no key pressed */
		return 0;
	/*
	 * Hauppauge remotes (black/silver) always use
	 * specific device ids. If we do not filter the
	 * device ids then messages destined for devices
	 * such as TVs (id=0) will get through causing
	 * mis-fired events.
	 *
	 * We also filter out invalid key presses which
	 * produce annoying debug log entries.
	 */
	ircode= (start << 12) | (toggle << 11) | (dev << 6) | code;
	if ((ircode & 0x1fff)==0x1fff)
		/* invalid key press */
		return 0;

	if (dev!=0x1e && dev!=0x1f)
		/* not a hauppauge remote */
		return 0;

	if (!range)
		code += 64;

	dprintk(1,"ir hauppauge (rc5): s%d r%d t%d dev=%d code=%d\n",
		start, range, toggle, dev, code);

	/* return key */
	*ir_key = code;
	*ir_raw = ircode;
	return 1;
}