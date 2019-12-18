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
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int megasas_generic_reset (struct scsi_cmnd*) ; 

__attribute__((used)) static int megasas_reset_device(struct scsi_cmnd *scmd)
{
	int ret;

	/*
	 * First wait for all commands to complete
	 */
	ret = megasas_generic_reset(scmd);

	return ret;
}