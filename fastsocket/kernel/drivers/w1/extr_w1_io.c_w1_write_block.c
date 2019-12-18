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
typedef  int /*<<< orphan*/  u8 ;
struct w1_master {TYPE_1__* bus_master; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* write_block ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  w1_post_write (struct w1_master*) ; 
 int /*<<< orphan*/  w1_pre_write (struct w1_master*) ; 
 int /*<<< orphan*/  w1_write_8 (struct w1_master*,int /*<<< orphan*/  const) ; 

void w1_write_block(struct w1_master *dev, const u8 *buf, int len)
{
	int i;

	if (dev->bus_master->write_block) {
		w1_pre_write(dev);
		dev->bus_master->write_block(dev->bus_master->data, buf, len);
	}
	else
		for (i = 0; i < len; ++i)
			w1_write_8(dev, buf[i]); /* calls w1_pre_write */
	w1_post_write(dev);
}