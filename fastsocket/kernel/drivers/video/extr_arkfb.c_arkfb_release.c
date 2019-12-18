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
struct fb_info {struct arkfb_info* par; } ;
struct arkfb_info {int ref_count; int /*<<< orphan*/  open_lock; int /*<<< orphan*/  dac; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC_PSEUDO8_8 ; 
 int EINVAL ; 
 int /*<<< orphan*/  dac_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  restore_vga (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int arkfb_release(struct fb_info *info, int user)
{
	struct arkfb_info *par = info->par;

	mutex_lock(&(par->open_lock));
	if (par->ref_count == 0) {
		mutex_unlock(&(par->open_lock));
		return -EINVAL;
	}

	if (par->ref_count == 1) {
		restore_vga(&(par->state));
		dac_set_mode(par->dac, DAC_PSEUDO8_8);
	}

	par->ref_count--;
	mutex_unlock(&(par->open_lock));

	return 0;
}