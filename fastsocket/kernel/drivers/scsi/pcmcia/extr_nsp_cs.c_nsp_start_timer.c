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
struct scsi_cmnd {TYPE_2__* device; } ;
struct TYPE_6__ {int TimerCount; } ;
typedef  TYPE_3__ nsp_hw_data ;
struct TYPE_5__ {TYPE_1__* host; } ;
struct TYPE_4__ {unsigned int io_port; scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMERCOUNT ; 
 int /*<<< orphan*/  nsp_index_write (unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nsp_start_timer(struct scsi_cmnd *SCpnt, int time)
{
	unsigned int base = SCpnt->device->host->io_port;
	nsp_hw_data *data = (nsp_hw_data *)SCpnt->device->host->hostdata;

	//nsp_dbg(NSP_DEBUG_INTR, "in SCpnt=0x%p, time=%d", SCpnt, time);
	data->TimerCount = time;
	nsp_index_write(base, TIMERCOUNT, time);
}