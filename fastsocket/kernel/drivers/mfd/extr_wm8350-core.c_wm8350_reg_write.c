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
struct wm8350 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  io_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wm8350_write (struct wm8350*,int,int,int /*<<< orphan*/ *) ; 

int wm8350_reg_write(struct wm8350 *wm8350, int reg, u16 val)
{
	int ret;
	u16 data = val;

	mutex_lock(&io_mutex);
	ret = wm8350_write(wm8350, reg, 1, &data);
	if (ret)
		dev_err(wm8350->dev, "write to reg R%d failed\n", reg);
	mutex_unlock(&io_mutex);
	return ret;
}