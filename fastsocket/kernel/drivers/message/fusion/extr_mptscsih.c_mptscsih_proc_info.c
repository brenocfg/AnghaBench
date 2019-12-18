#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_3__ {int /*<<< orphan*/ * ioc; } ;
typedef  TYPE_1__ MPT_SCSI_HOST ;
typedef  int /*<<< orphan*/  MPT_ADAPTER ;

/* Variables and functions */
 int mptscsih_host_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* shost_priv (struct Scsi_Host*) ; 

int
mptscsih_proc_info(struct Scsi_Host *host, char *buffer, char **start, off_t offset,
			int length, int func)
{
	MPT_SCSI_HOST	*hd = shost_priv(host);
	MPT_ADAPTER	*ioc = hd->ioc;
	int size = 0;

	if (func) {
		/*
		 * write is not supported
		 */
	} else {
		if (start)
			*start = buffer;

		size = mptscsih_host_info(ioc, buffer, offset, length);
	}

	return size;
}