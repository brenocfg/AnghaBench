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
typedef  int u8 ;
struct dvb_usb_device {int dummy; } ;
typedef  int fe_bandwidth_t ;

/* Variables and functions */
#define  BANDWIDTH_6_MHZ 130 
#define  BANDWIDTH_7_MHZ 129 
#define  BANDWIDTH_8_MHZ 128 
 int EINVAL ; 
 int af9005_write_register_bits (struct dvb_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int /*<<< orphan*/  reg_bw_len ; 
 int /*<<< orphan*/  reg_bw_pos ; 
 int /*<<< orphan*/  xd_g_reg_bw ; 

__attribute__((used)) static int af9005_fe_select_bw(struct dvb_usb_device *d, fe_bandwidth_t bw)
{
	u8 temp;
	switch (bw) {
	case BANDWIDTH_6_MHZ:
		temp = 0;
		break;
	case BANDWIDTH_7_MHZ:
		temp = 1;
		break;
	case BANDWIDTH_8_MHZ:
		temp = 2;
		break;
	default:
		err("Invalid bandwith %d.", bw);
		return -EINVAL;
	}
	return af9005_write_register_bits(d, xd_g_reg_bw, reg_bw_pos,
					  reg_bw_len, temp);
}