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
typedef  scalar_t__ uint16_t ;
struct scsi_qla_host {scalar_t__ pri_ddb_idx; scalar_t__ sec_ddb_idx; } ;

/* Variables and functions */
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 scalar_t__ ql4xdisablesysfsboot ; 

__attribute__((used)) static int qla4xxx_verify_boot_idx(struct scsi_qla_host *ha, uint16_t idx)
{
	if (ql4xdisablesysfsboot)
		return QLA_SUCCESS;
	if (idx == ha->pri_ddb_idx || idx == ha->sec_ddb_idx)
		return QLA_ERROR;
	return QLA_SUCCESS;
}