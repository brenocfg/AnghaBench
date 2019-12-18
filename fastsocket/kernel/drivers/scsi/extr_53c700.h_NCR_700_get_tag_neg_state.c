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
typedef  enum NCR_700_tag_neg_state { ____Placeholder_NCR_700_tag_neg_state } NCR_700_tag_neg_state ;

/* Variables and functions */
 int spi_flags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline enum NCR_700_tag_neg_state
NCR_700_get_tag_neg_state(struct scsi_device *SDp)
{
	return (enum NCR_700_tag_neg_state)((spi_flags(SDp->sdev_target)>>20) & 0x3);
}