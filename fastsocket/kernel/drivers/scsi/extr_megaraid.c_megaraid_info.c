#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {scalar_t__ hostdata; } ;
struct TYPE_4__ {int max_commands; } ;
struct TYPE_6__ {char* fw_version; TYPE_2__* host; TYPE_1__ product_info; } ;
typedef  TYPE_3__ adapter_t ;
struct TYPE_5__ {int max_id; int max_channel; int max_lun; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*,int,int,int,int) ; 

const char *
megaraid_info(struct Scsi_Host *host)
{
	static char buffer[512];
	adapter_t *adapter;

	adapter = (adapter_t *)host->hostdata;

	sprintf (buffer,
		 "LSI Logic MegaRAID %s %d commands %d targs %d chans %d luns",
		 adapter->fw_version, adapter->product_info.max_commands,
		 adapter->host->max_id, adapter->host->max_channel,
		 adapter->host->max_lun);
	return buffer;
}