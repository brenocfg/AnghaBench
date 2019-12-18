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
struct vp702x_fe_state {int status_check_interval; scalar_t__ next_status_check; int /*<<< orphan*/  sig; int /*<<< orphan*/  d; int /*<<< orphan*/  snr; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  READ_STATUS ; 
 int /*<<< orphan*/  READ_TUNER_REG_REQ ; 
 scalar_t__ jiffies ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vp702x_usb_in_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vp702x_fe_refresh_state(struct vp702x_fe_state *st)
{
	u8 buf[10];
	if (time_after(jiffies,st->next_status_check)) {
		vp702x_usb_in_op(st->d,READ_STATUS,0,0,buf,10);

		st->lock = buf[4];
		vp702x_usb_in_op(st->d,READ_TUNER_REG_REQ,0x11,0,&st->snr,1);
		vp702x_usb_in_op(st->d,READ_TUNER_REG_REQ,0x15,0,&st->sig,1);

		st->next_status_check = jiffies + (st->status_check_interval*HZ)/1000;
	}
	return 0;
}