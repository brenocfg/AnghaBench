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
typedef  union viosrp_iu {int dummy; } viosrp_iu ;
struct vio_dev {int dummy; } ;

/* Variables and functions */
 int IBMVSCSI_CMDS_PER_LUN_DEFAULT ; 
 int IBMVSCSI_MAX_SECTORS_DEFAULT ; 
 int max_events ; 

__attribute__((used)) static unsigned long ibmvscsi_get_desired_dma(struct vio_dev *vdev)
{
	/* iu_storage data allocated in initialize_event_pool */
	unsigned long desired_io = max_events * sizeof(union viosrp_iu);

	/* add io space for sg data */
	desired_io += (IBMVSCSI_MAX_SECTORS_DEFAULT * 512 *
	                     IBMVSCSI_CMDS_PER_LUN_DEFAULT);

	return desired_io;
}