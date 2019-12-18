#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct aac_dev {TYPE_2__* scsi_host_ptr; TYPE_1__* init; } ;
struct TYPE_4__ {scalar_t__ can_queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  MaxIoCommands; } ;

/* Variables and functions */
 int AAC_COMM_MESSAGE ; 
 scalar_t__ AAC_NUM_IO_FIB_RKT ; 
 scalar_t__ AAC_NUM_MGT_FIB ; 
 int aac_rx_select_comm (struct aac_dev*,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 

__attribute__((used)) static int aac_rkt_select_comm(struct aac_dev *dev, int comm)
{
	int retval;
	retval = aac_rx_select_comm(dev, comm);
	if (comm == AAC_COMM_MESSAGE) {
		/*
		 * FIB Setup has already been done, but we can minimize the
		 * damage by at least ensuring the OS never issues more
		 * commands than we can handle. The Rocket adapters currently
		 * can only handle 246 commands and 8 AIFs at the same time,
		 * and in fact do notify us accordingly if we negotiate the
		 * FIB size. The problem that causes us to add this check is
		 * to ensure that we do not overdo it with the adapter when a
		 * hard coded FIB override is being utilized. This special
		 * case warrants this half baked, but convenient, check here.
		 */
		if (dev->scsi_host_ptr->can_queue > AAC_NUM_IO_FIB_RKT) {
			dev->init->MaxIoCommands =
				cpu_to_le32(AAC_NUM_IO_FIB_RKT + AAC_NUM_MGT_FIB);
			dev->scsi_host_ptr->can_queue = AAC_NUM_IO_FIB_RKT;
		}
	}
	return retval;
}