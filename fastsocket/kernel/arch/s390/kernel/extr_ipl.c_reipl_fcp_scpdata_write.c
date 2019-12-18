#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  size_t ssize_t ;
typedef  size_t loff_t ;
struct TYPE_7__ {scalar_t__ blk0_len; scalar_t__ len; } ;
struct TYPE_5__ {size_t scp_data_len; scalar_t__ scp_data; } ;
struct TYPE_6__ {TYPE_1__ fcp; } ;
struct TYPE_8__ {TYPE_3__ hdr; TYPE_2__ ipl_info; } ;

/* Variables and functions */
 size_t DIAG308_SCPDATA_SIZE ; 
 size_t EINVAL ; 
 size_t ENOSPC ; 
 scalar_t__ IPL_PARM_BLK0_FCP_LEN ; 
 scalar_t__ IPL_PARM_BLK_FCP_LEN ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,size_t) ; 
 TYPE_4__* reipl_block_fcp ; 

__attribute__((used)) static ssize_t reipl_fcp_scpdata_write(struct file *filp, struct kobject *kobj,
				       struct bin_attribute *attr,
				       char *buf, loff_t off, size_t count)
{
	size_t padding;
	size_t scpdata_len;

	if (off < 0)
		return -EINVAL;

	if (off >= DIAG308_SCPDATA_SIZE)
		return -ENOSPC;

	if (count > DIAG308_SCPDATA_SIZE - off)
		count = DIAG308_SCPDATA_SIZE - off;

	memcpy(reipl_block_fcp->ipl_info.fcp.scp_data, buf + off, count);
	scpdata_len = off + count;

	if (scpdata_len % 8) {
		padding = 8 - (scpdata_len % 8);
		memset(reipl_block_fcp->ipl_info.fcp.scp_data + scpdata_len,
		       0, padding);
		scpdata_len += padding;
	}

	reipl_block_fcp->ipl_info.fcp.scp_data_len = scpdata_len;
	reipl_block_fcp->hdr.len = IPL_PARM_BLK_FCP_LEN + scpdata_len;
	reipl_block_fcp->hdr.blk0_len = IPL_PARM_BLK0_FCP_LEN + scpdata_len;

	return count;
}