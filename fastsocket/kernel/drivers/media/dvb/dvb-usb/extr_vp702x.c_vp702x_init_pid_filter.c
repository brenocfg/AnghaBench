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
struct vp702x_state {int pid_filter_count; int pid_filter_can_bypass; int pid_filter_state; } ;
struct dvb_usb_adapter {int /*<<< orphan*/  dev; struct vp702x_state* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  vp702x_set_pid (struct dvb_usb_adapter*,int,int,int) ; 
 int /*<<< orphan*/  vp702x_set_pld_mode (struct dvb_usb_adapter*,int) ; 
 int /*<<< orphan*/  vp702x_usb_in_op (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vp702x_init_pid_filter(struct dvb_usb_adapter *adap)
{
	struct vp702x_state *st = adap->priv;
	int i;
	u8 b[10] = { 0 };

	st->pid_filter_count = 8;
	st->pid_filter_can_bypass = 1;
	st->pid_filter_state = 0x00;

	vp702x_set_pld_mode(adap, 1); // bypass

	for (i = 0; i < st->pid_filter_count; i++)
		vp702x_set_pid(adap, 0xffff, i, 1);

	vp702x_usb_in_op(adap->dev, 0xb5, 3, 0, b, 10);
	vp702x_usb_in_op(adap->dev, 0xb5, 0, 0, b, 10);
	vp702x_usb_in_op(adap->dev, 0xb5, 1, 0, b, 10);

	//vp702x_set_pld_mode(d, 0); // filter
	return 0;
}