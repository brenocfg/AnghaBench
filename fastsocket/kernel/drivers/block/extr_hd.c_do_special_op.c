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
struct request {TYPE_1__* rq_disk; } ;
struct hd_i_struct {int head; scalar_t__ special_op; int /*<<< orphan*/  sect; scalar_t__ recalibrate; } ;
struct TYPE_2__ {int /*<<< orphan*/  disk_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CMD_RESTORE ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  hd_end_request_cur (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hd_out (struct hd_i_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recal_intr ; 
 int reset ; 

__attribute__((used)) static int do_special_op(struct hd_i_struct *disk, struct request *req)
{
	if (disk->recalibrate) {
		disk->recalibrate = 0;
		hd_out(disk, disk->sect, 0, 0, 0, ATA_CMD_RESTORE, &recal_intr);
		return reset;
	}
	if (disk->head > 16) {
		printk("%s: cannot handle device with more than 16 heads - giving up\n", req->rq_disk->disk_name);
		hd_end_request_cur(-EIO);
	}
	disk->special_op = 0;
	return 1;
}