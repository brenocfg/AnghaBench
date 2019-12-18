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
struct wm8400 {int (* read_dev ) (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * reg_cache; int /*<<< orphan*/  io_data; } ;
struct TYPE_2__ {scalar_t__ vol; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* reg_data ; 
 int stub1 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wm8400_read(struct wm8400 *wm8400, u8 reg, int num_regs, u16 *dest)
{
	int i, ret = 0;

	BUG_ON(reg + num_regs - 1 > ARRAY_SIZE(wm8400->reg_cache));

	/* If there are any volatile reads then read back the entire block */
	for (i = reg; i < reg + num_regs; i++)
		if (reg_data[i].vol) {
			ret = wm8400->read_dev(wm8400->io_data, reg,
					       num_regs, dest);
			if (ret != 0)
				return ret;
			for (i = 0; i < num_regs; i++)
				dest[i] = be16_to_cpu(dest[i]);

			return 0;
		}

	/* Otherwise use the cache */
	memcpy(dest, &wm8400->reg_cache[reg], num_regs * sizeof(u16));

	return 0;
}