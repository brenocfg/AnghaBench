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
struct ipr_ioa_cfg {int type; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static const char * ipr_ioa_info(struct Scsi_Host *host)
{
	static char buffer[512];
	struct ipr_ioa_cfg *ioa_cfg;
	unsigned long lock_flags = 0;

	ioa_cfg = (struct ipr_ioa_cfg *) host->hostdata;

	spin_lock_irqsave(host->host_lock, lock_flags);
	sprintf(buffer, "IBM %X Storage Adapter", ioa_cfg->type);
	spin_unlock_irqrestore(host->host_lock, lock_flags);

	return buffer;
}