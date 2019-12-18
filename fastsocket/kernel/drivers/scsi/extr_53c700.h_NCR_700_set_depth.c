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
struct scsi_device {struct NCR_700_Device_Parameters* hostdata; } ;
struct NCR_700_Device_Parameters {int /*<<< orphan*/  depth; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */

__attribute__((used)) static inline void
NCR_700_set_depth(struct scsi_device *SDp, __u8 depth)
{
	struct NCR_700_Device_Parameters *hostdata = SDp->hostdata;

	hostdata->depth = depth;
}