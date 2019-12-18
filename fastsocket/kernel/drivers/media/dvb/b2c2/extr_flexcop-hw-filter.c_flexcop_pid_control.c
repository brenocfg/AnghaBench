#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct flexcop_device {int /*<<< orphan*/  (* write_ibi_reg ) (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_3__) ;TYPE_3__ (* read_ibi_reg ) (struct flexcop_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  has_32_hw_pid_filter; } ;
struct TYPE_9__ {int PID; int PID_enable_bit; } ;
struct TYPE_8__ {int index_reg; } ;
struct TYPE_10__ {TYPE_2__ pid_n_reg_314; TYPE_1__ index_reg_310; } ;
typedef  TYPE_3__ flexcop_ibi_value ;

/* Variables and functions */
 int /*<<< orphan*/  deb_ts (char*,int,int,int,char*) ; 
 int /*<<< orphan*/  flexcop_pid_ECM_PID_ctrl (struct flexcop_device*,int,int) ; 
 int /*<<< orphan*/  flexcop_pid_EMM_PID_ctrl (struct flexcop_device*,int,int) ; 
 int /*<<< orphan*/  flexcop_pid_PCR_PID_ctrl (struct flexcop_device*,int,int) ; 
 int /*<<< orphan*/  flexcop_pid_PMT_PID_ctrl (struct flexcop_device*,int,int) ; 
 int /*<<< orphan*/  flexcop_pid_Stream1_PID_ctrl (struct flexcop_device*,int,int) ; 
 int /*<<< orphan*/  flexcop_pid_Stream2_PID_ctrl (struct flexcop_device*,int,int) ; 
 int /*<<< orphan*/  index_reg_310 ; 
 int /*<<< orphan*/  pid_n_reg_314 ; 
 TYPE_3__ stub1 (struct flexcop_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_3__) ; 
 TYPE_3__ stub3 (struct flexcop_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_3__) ; 

__attribute__((used)) static void flexcop_pid_control(struct flexcop_device *fc,
		int index, u16 pid, int onoff)
{
	if (pid == 0x2000)
		return;

	deb_ts("setting pid: %5d %04x at index %d '%s'\n",
			pid, pid, index, onoff ? "on" : "off");

	/* We could use bit magic here to reduce source code size.
	 * I decided against it, but to use the real register names */
	switch (index) {
	case 0:
		flexcop_pid_Stream1_PID_ctrl(fc, pid, onoff);
		break;
	case 1:
		flexcop_pid_Stream2_PID_ctrl(fc, pid, onoff);
		break;
	case 2:
		flexcop_pid_PCR_PID_ctrl(fc, pid, onoff);
		break;
	case 3:
		flexcop_pid_PMT_PID_ctrl(fc, pid, onoff);
		break;
	case 4:
		flexcop_pid_EMM_PID_ctrl(fc, pid, onoff);
		break;
	case 5:
		flexcop_pid_ECM_PID_ctrl(fc, pid, onoff);
		break;
	default:
		if (fc->has_32_hw_pid_filter && index < 38) {
			flexcop_ibi_value vpid, vid;

			/* set the index */
			vid = fc->read_ibi_reg(fc, index_reg_310);
			vid.index_reg_310.index_reg = index - 6;
			fc->write_ibi_reg(fc, index_reg_310, vid);

			vpid = fc->read_ibi_reg(fc, pid_n_reg_314);
			vpid.pid_n_reg_314.PID = onoff ? pid : 0x1fff;
			vpid.pid_n_reg_314.PID_enable_bit = onoff;
			fc->write_ibi_reg(fc, pid_n_reg_314, vpid);
		}
		break;
	}
}