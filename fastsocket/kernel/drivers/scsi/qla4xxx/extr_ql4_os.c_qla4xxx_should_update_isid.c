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
struct scsi_qla_host {int dummy; } ;
struct ql4_tuple_ddb {scalar_t__ port; int /*<<< orphan*/ * isid; int /*<<< orphan*/  iscsi_name; int /*<<< orphan*/  ip_addr; } ;

/* Variables and functions */
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qla4xxx_should_update_isid(struct scsi_qla_host *ha,
				      struct ql4_tuple_ddb *old_tddb,
				      struct ql4_tuple_ddb *new_tddb)
{
	if (strcmp(old_tddb->ip_addr, new_tddb->ip_addr) == 0) {
		/* Same ip */
		if (old_tddb->port == new_tddb->port)
			return QLA_ERROR;
	}

	if (strcmp(old_tddb->iscsi_name, new_tddb->iscsi_name))
		/* different iqn */
		return QLA_ERROR;

	if (memcmp(&old_tddb->isid[0], &new_tddb->isid[0],
		   sizeof(old_tddb->isid)))
		/* different isid */
		return QLA_ERROR;

	return QLA_SUCCESS;
}