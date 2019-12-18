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
struct scsi_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ scsi_device_tpgs (struct scsi_device*) ; 

__attribute__((used)) static bool alua_match(struct scsi_device *sdev)
{
	return (scsi_device_tpgs(sdev) != 0);
}