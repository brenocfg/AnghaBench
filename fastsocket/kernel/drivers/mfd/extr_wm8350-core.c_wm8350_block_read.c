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
 int wm8350_read (struct wm8350*,int,int,int /*<<< orphan*/ *) ; 

int wm8350_block_read(struct wm8350 *wm8350, int start_reg, int regs,
		      u16 *dest)
{
	int err = 0;

	mutex_lock(&io_mutex);
	err = wm8350_read(wm8350, start_reg, regs, dest);
	if (err)
		dev_err(wm8350->dev, "block read starting from R%d failed\n",
			start_reg);
	mutex_unlock(&io_mutex);
	return err;
}