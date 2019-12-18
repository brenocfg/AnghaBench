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
typedef  scalar_t__ u32 ;
struct qlcnic_hardware_context {int dummy; } ;
struct qlcnic_adapter {struct qlcnic_hardware_context* ahw; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_FW_MBX_CTRL ; 
 scalar_t__ QLCNIC_MBX_TIMEOUT ; 
 scalar_t__ QLCNIC_RCODE_TIMEOUT ; 
 scalar_t__ QLCRDX (struct qlcnic_hardware_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

u32 qlcnic_83xx_mbx_poll(struct qlcnic_adapter *adapter, u32 *wait_time)
{
	u32 data;
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	/* wait for mailbox completion */
	do {
		data = QLCRDX(ahw, QLCNIC_FW_MBX_CTRL);
		if (++(*wait_time) > QLCNIC_MBX_TIMEOUT) {
			data = QLCNIC_RCODE_TIMEOUT;
			break;
		}
		mdelay(1);
	} while (!data);
	return data;
}