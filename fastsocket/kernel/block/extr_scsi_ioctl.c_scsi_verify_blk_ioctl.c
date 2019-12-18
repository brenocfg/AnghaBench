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
struct block_device {struct block_device* bd_contains; } ;

/* Variables and functions */
 int ENOTTY ; 
#define  SCSI_IOCTL_GET_BUS_NUMBER 137 
#define  SCSI_IOCTL_GET_IDLUN 136 
#define  SCSI_IOCTL_GET_PCI 135 
#define  SCSI_IOCTL_PROBE_HOST 134 
#define  SG_EMULATED_HOST 133 
#define  SG_GET_RESERVED_SIZE 132 
#define  SG_GET_TIMEOUT 131 
#define  SG_GET_VERSION_NUM 130 
#define  SG_SET_RESERVED_SIZE 129 
#define  SG_SET_TIMEOUT 128 

int scsi_verify_blk_ioctl(struct block_device *bd, unsigned int cmd)
{
	if (bd && bd == bd->bd_contains)
		return 0;

	/* Actually none of this is particularly useful on a partition
	 * device, but let's play it safe.
	 */
	switch (cmd) {
	case SCSI_IOCTL_GET_IDLUN:
	case SCSI_IOCTL_GET_BUS_NUMBER:
	case SCSI_IOCTL_GET_PCI:
	case SCSI_IOCTL_PROBE_HOST:
	case SG_GET_VERSION_NUM:
	case SG_SET_TIMEOUT:
	case SG_GET_TIMEOUT:
	case SG_GET_RESERVED_SIZE:
	case SG_SET_RESERVED_SIZE:
	case SG_EMULATED_HOST:
		return 0;
	default:
		break;
	}
	/* In particular, rule out all resets and host-specific ioctls.  */
	return -ENOTTY;
}