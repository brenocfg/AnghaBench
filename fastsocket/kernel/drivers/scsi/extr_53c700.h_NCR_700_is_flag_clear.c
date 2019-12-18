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
struct scsi_device {int /*<<< orphan*/  sdev_target; } ;
typedef  int __u32 ;

/* Variables and functions */
 int spi_flags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
NCR_700_is_flag_clear(struct scsi_device *SDp, __u32 flag)
{
	return (spi_flags(SDp->sdev_target) & flag) == 0;
}