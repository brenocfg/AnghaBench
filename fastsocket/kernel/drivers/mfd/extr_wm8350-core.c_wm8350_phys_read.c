#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wm8350 {int (* read_dev ) (struct wm8350*,int,int,char*) ;int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  readable; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dump (int,int /*<<< orphan*/ *) ; 
 int stub1 (struct wm8350*,int,int,char*) ; 
 TYPE_1__* wm8350_reg_io_map ; 

__attribute__((used)) static int wm8350_phys_read(struct wm8350 *wm8350, u8 reg, int num_regs,
			    u16 *dest)
{
	int i, ret;
	int bytes = num_regs * 2;

	dev_dbg(wm8350->dev, "volatile read\n");
	ret = wm8350->read_dev(wm8350, reg, bytes, (char *)dest);

	for (i = reg; i < reg + num_regs; i++) {
		/* Cache is CPU endian */
		dest[i - reg] = be16_to_cpu(dest[i - reg]);

		/* Mask out non-readable bits */
		dest[i - reg] &= wm8350_reg_io_map[i].readable;
	}

	dump(num_regs, dest);

	return ret;
}