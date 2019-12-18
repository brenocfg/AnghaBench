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
struct hd_i_struct {int special_op; int recalibrate; int /*<<< orphan*/  cyl; scalar_t__ head; int /*<<< orphan*/  sect; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CMD_INIT_DEV_PARAMS ; 
 int NR_HD ; 
 int /*<<< orphan*/  check_status () ; 
 struct hd_i_struct* hd_info ; 
 int /*<<< orphan*/  hd_out (struct hd_i_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) ()) ; 
 int /*<<< orphan*/  hd_request () ; 
 scalar_t__ reset ; 
 int /*<<< orphan*/  reset_controller () ; 

__attribute__((used)) static void reset_hd(void)
{
	static int i;

repeat:
	if (reset) {
		reset = 0;
		i = -1;
		reset_controller();
	} else {
		check_status();
		if (reset)
			goto repeat;
	}
	if (++i < NR_HD) {
		struct hd_i_struct *disk = &hd_info[i];
		disk->special_op = disk->recalibrate = 1;
		hd_out(disk, disk->sect, disk->sect, disk->head-1,
			disk->cyl, ATA_CMD_INIT_DEV_PARAMS, &reset_hd);
		if (reset)
			goto repeat;
	} else
		hd_request();
}