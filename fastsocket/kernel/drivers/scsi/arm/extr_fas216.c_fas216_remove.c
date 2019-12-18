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
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  FAS216_Info ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RESETCHIP ; 
 int /*<<< orphan*/  REG_CMD ; 
 int /*<<< orphan*/  fas216_checkmagic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fas216_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 

void fas216_remove(struct Scsi_Host *host)
{
	FAS216_Info *info = (FAS216_Info *)host->hostdata;

	fas216_checkmagic(info);
	scsi_remove_host(host);

	fas216_writeb(info, REG_CMD, CMD_RESETCHIP);
	scsi_host_put(host);
}