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
typedef  unsigned short u16 ;
struct wm831x {int /*<<< orphan*/  io_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wm831x_read (struct wm831x*,unsigned short,int,unsigned short*) ; 
 int wm831x_write (struct wm831x*,unsigned short,int,unsigned short*) ; 

int wm831x_set_bits(struct wm831x *wm831x, unsigned short reg,
		    unsigned short mask, unsigned short val)
{
	int ret;
	u16 r;

	mutex_lock(&wm831x->io_lock);

	ret = wm831x_read(wm831x, reg, 2, &r);
	if (ret < 0)
		goto out;

	r &= ~mask;
	r |= val;

	ret = wm831x_write(wm831x, reg, 2, &r);

out:
	mutex_unlock(&wm831x->io_lock);

	return ret;
}