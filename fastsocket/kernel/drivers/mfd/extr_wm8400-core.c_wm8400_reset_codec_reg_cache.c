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
struct wm8400 {int /*<<< orphan*/  io_lock; int /*<<< orphan*/ * reg_cache; } ;
struct TYPE_2__ {int /*<<< orphan*/  default_val; scalar_t__ is_codec; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* reg_data ; 

void wm8400_reset_codec_reg_cache(struct wm8400 *wm8400)
{
	int i;

	mutex_lock(&wm8400->io_lock);

	/* Reset all codec registers to their initial value */
	for (i = 0; i < ARRAY_SIZE(wm8400->reg_cache); i++)
		if (reg_data[i].is_codec)
			wm8400->reg_cache[i] = reg_data[i].default_val;

	mutex_unlock(&wm8400->io_lock);
}