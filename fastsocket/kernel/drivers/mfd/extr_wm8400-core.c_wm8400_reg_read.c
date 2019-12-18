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
typedef  int /*<<< orphan*/  u16 ;
struct wm8400 {int /*<<< orphan*/  io_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wm8400_read (struct wm8400*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

u16 wm8400_reg_read(struct wm8400 *wm8400, u8 reg)
{
	u16 val;

	mutex_lock(&wm8400->io_lock);

	wm8400_read(wm8400, reg, 1, &val);

	mutex_unlock(&wm8400->io_lock);

	return val;
}