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
struct sdebug_dev_info {int channel; TYPE_2__* sdbg_host; } ;
struct scsi_cmnd {scalar_t__ cmnd; } ;
struct TYPE_4__ {TYPE_1__* shost; } ;
struct TYPE_3__ {int host_no; } ;

/* Variables and functions */
 int DID_REQUEUE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int SDEBUG_MAX_TGTPGS_ARR_SZ ; 
 int fill_from_dev_buffer (struct scsi_cmnd*,unsigned char*,int) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 scalar_t__ scsi_debug_vpd_use_hostno ; 

__attribute__((used)) static int resp_report_tgtpgs(struct scsi_cmnd * scp,
			      struct sdebug_dev_info * devip)
{
	unsigned char *cmd = (unsigned char *)scp->cmnd;
	unsigned char * arr;
	int host_no = devip->sdbg_host->shost->host_no;
	int n, ret, alen, rlen;
	int port_group_a, port_group_b, port_a, port_b;

	alen = ((cmd[6] << 24) + (cmd[7] << 16) + (cmd[8] << 8)
		+ cmd[9]);

	arr = kzalloc(SDEBUG_MAX_TGTPGS_ARR_SZ, GFP_ATOMIC);
	if (! arr)
		return DID_REQUEUE << 16;
	/*
	 * EVPD page 0x88 states we have two ports, one
	 * real and a fake port with no device connected.
	 * So we create two port groups with one port each
	 * and set the group with port B to unavailable.
	 */
	port_a = 0x1; /* relative port A */
	port_b = 0x2; /* relative port B */
	port_group_a = (((host_no + 1) & 0x7f) << 8) +
	    (devip->channel & 0x7f);
	port_group_b = (((host_no + 1) & 0x7f) << 8) +
	    (devip->channel & 0x7f) + 0x80;

	/*
	 * The asymmetric access state is cycled according to the host_id.
	 */
	n = 4;
	if (0 == scsi_debug_vpd_use_hostno) {
	    arr[n++] = host_no % 3; /* Asymm access state */
	    arr[n++] = 0x0F; /* claim: all states are supported */
	} else {
	    arr[n++] = 0x0; /* Active/Optimized path */
	    arr[n++] = 0x01; /* claim: only support active/optimized paths */
	}
	arr[n++] = (port_group_a >> 8) & 0xff;
	arr[n++] = port_group_a & 0xff;
	arr[n++] = 0;    /* Reserved */
	arr[n++] = 0;    /* Status code */
	arr[n++] = 0;    /* Vendor unique */
	arr[n++] = 0x1;  /* One port per group */
	arr[n++] = 0;    /* Reserved */
	arr[n++] = 0;    /* Reserved */
	arr[n++] = (port_a >> 8) & 0xff;
	arr[n++] = port_a & 0xff;
	arr[n++] = 3;    /* Port unavailable */
	arr[n++] = 0x08; /* claim: only unavailalbe paths are supported */
	arr[n++] = (port_group_b >> 8) & 0xff;
	arr[n++] = port_group_b & 0xff;
	arr[n++] = 0;    /* Reserved */
	arr[n++] = 0;    /* Status code */
	arr[n++] = 0;    /* Vendor unique */
	arr[n++] = 0x1;  /* One port per group */
	arr[n++] = 0;    /* Reserved */
	arr[n++] = 0;    /* Reserved */
	arr[n++] = (port_b >> 8) & 0xff;
	arr[n++] = port_b & 0xff;

	rlen = n - 4;
	arr[0] = (rlen >> 24) & 0xff;
	arr[1] = (rlen >> 16) & 0xff;
	arr[2] = (rlen >> 8) & 0xff;
	arr[3] = rlen & 0xff;

	/*
	 * Return the smallest value of either
	 * - The allocated length
	 * - The constructed command length
	 * - The maximum array size
	 */
	rlen = min(alen,n);
	ret = fill_from_dev_buffer(scp, arr,
				   min(rlen, SDEBUG_MAX_TGTPGS_ARR_SZ));
	kfree(arr);
	return ret;
}