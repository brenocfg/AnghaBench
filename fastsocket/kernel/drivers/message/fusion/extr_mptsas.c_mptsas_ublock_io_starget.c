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
struct scsi_target {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mptsas_ublock_io_sdev ; 
 int /*<<< orphan*/  starget_for_each_device (struct scsi_target*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mptsas_ublock_io_starget(struct scsi_target *starget)
{
	if (starget)
		starget_for_each_device(starget, NULL, mptsas_ublock_io_sdev);
}