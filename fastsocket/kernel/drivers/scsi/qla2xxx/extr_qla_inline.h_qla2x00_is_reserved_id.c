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
typedef  scalar_t__ uint16_t ;
struct qla_hw_data {scalar_t__ max_loop_id; } ;
struct TYPE_3__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 scalar_t__ BROADCAST ; 
 scalar_t__ IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 scalar_t__ MANAGEMENT_SERVER ; 
 scalar_t__ NPH_LAST_HANDLE ; 
 scalar_t__ SNS_FIRST_LOOP_ID ; 

__attribute__((used)) static inline int
qla2x00_is_reserved_id(scsi_qla_host_t *vha, uint16_t loop_id)
{
	struct qla_hw_data *ha = vha->hw;
	if (IS_FWI2_CAPABLE(ha))
		return (loop_id > NPH_LAST_HANDLE);

	return ((loop_id > ha->max_loop_id && loop_id < SNS_FIRST_LOOP_ID) ||
	    loop_id == MANAGEMENT_SERVER || loop_id == BROADCAST);
}