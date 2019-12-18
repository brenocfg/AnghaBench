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
typedef  int /*<<< orphan*/  u16 ;
struct wm831x {int (* read_dev ) (struct wm831x*,unsigned short,int,void*) ;int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned short,unsigned short) ; 
 int stub1 (struct wm831x*,unsigned short,int,void*) ; 

__attribute__((used)) static int wm831x_read(struct wm831x *wm831x, unsigned short reg,
		       int bytes, void *dest)
{
	int ret, i;
	u16 *buf = dest;

	BUG_ON(bytes % 2);
	BUG_ON(bytes <= 0);

	ret = wm831x->read_dev(wm831x, reg, bytes, dest);
	if (ret < 0)
		return ret;

	for (i = 0; i < bytes / 2; i++) {
		buf[i] = be16_to_cpu(buf[i]);

		dev_vdbg(wm831x->dev, "Read %04x from R%d(0x%x)\n",
			 buf[i], reg + i, reg + i);
	}

	return 0;
}