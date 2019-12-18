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
struct scsi_cmnd {TYPE_2__* device; } ;
struct initio_host {int dummy; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_lock; scalar_t__ hostdata; } ;

/* Variables and functions */
 int SUCCESS ; 
 int /*<<< orphan*/  initio_reset_scsi (struct initio_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i91u_bus_reset(struct scsi_cmnd * cmnd)
{
	struct initio_host *host;

	host = (struct initio_host *) cmnd->device->host->hostdata;

	spin_lock_irq(cmnd->device->host->host_lock);
	initio_reset_scsi(host, 0);
	spin_unlock_irq(cmnd->device->host->host_lock);

	return SUCCESS;
}