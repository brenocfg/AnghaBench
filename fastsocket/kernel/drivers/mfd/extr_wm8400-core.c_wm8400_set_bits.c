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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct wm8400 {int /*<<< orphan*/  io_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wm8400_read (struct wm8400*,int /*<<< orphan*/ ,int,int*) ; 
 int wm8400_write (struct wm8400*,int /*<<< orphan*/ ,int,int*) ; 

int wm8400_set_bits(struct wm8400 *wm8400, u8 reg, u16 mask, u16 val)
{
	u16 tmp;
	int ret;

	mutex_lock(&wm8400->io_lock);

	ret = wm8400_read(wm8400, reg, 1, &tmp);
	tmp = (tmp & ~mask) | val;
	if (ret == 0)
		ret = wm8400_write(wm8400, reg, 1, &tmp);

	mutex_unlock(&wm8400->io_lock);

	return ret;
}