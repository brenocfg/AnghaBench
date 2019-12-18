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
struct tcm_loop_hba {struct Scsi_Host* sh; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 struct tcm_loop_hba* to_tcm_loop_hba (struct device*) ; 

__attribute__((used)) static int tcm_loop_driver_remove(struct device *dev)
{
	struct tcm_loop_hba *tl_hba;
	struct Scsi_Host *sh;

	tl_hba = to_tcm_loop_hba(dev);
	sh = tl_hba->sh;

	scsi_remove_host(sh);
	scsi_host_put(sh);
	return 0;
}