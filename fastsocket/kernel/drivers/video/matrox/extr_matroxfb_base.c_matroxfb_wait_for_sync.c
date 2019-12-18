#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct matrox_vsync {unsigned int cnt; int /*<<< orphan*/  wait; } ;
struct TYPE_4__ {struct matrox_vsync vsync; } ;
struct TYPE_6__ {int /*<<< orphan*/  accelerator; } ;
struct TYPE_5__ {struct matrox_vsync vsync; } ;
struct matrox_fb_info {TYPE_1__ crtc2; TYPE_3__ devflags; TYPE_2__ crtc1; } ;

/* Variables and functions */
 int ENODEV ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  FB_ACCEL_MATROX_MGAG400 ; 
 int HZ ; 
 int matroxfb_enable_irq (struct matrox_fb_info*,int) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

int matroxfb_wait_for_sync(struct matrox_fb_info *minfo, u_int32_t crtc)
{
	struct matrox_vsync *vs;
	unsigned int cnt;
	int ret;

	switch (crtc) {
		case 0:
			vs = &minfo->crtc1.vsync;
			break;
		case 1:
			if (minfo->devflags.accelerator != FB_ACCEL_MATROX_MGAG400) {
				return -ENODEV;
			}
			vs = &minfo->crtc2.vsync;
			break;
		default:
			return -ENODEV;
	}
	ret = matroxfb_enable_irq(minfo, 0);
	if (ret) {
		return ret;
	}

	cnt = vs->cnt;
	ret = wait_event_interruptible_timeout(vs->wait, cnt != vs->cnt, HZ/10);
	if (ret < 0) {
		return ret;
	}
	if (ret == 0) {
		matroxfb_enable_irq(minfo, 1);
		return -ETIMEDOUT;
	}
	return 0;
}