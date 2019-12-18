#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSDP_DI_RECORD ;
typedef  int /*<<< orphan*/  tBTA_STATUS ;
struct TYPE_4__ {int /*<<< orphan*/  primary_record; } ;
typedef  TYPE_1__ tBTA_DI_RECORD ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_5__ {size_t di_num; int /*<<< orphan*/ * di_handle; } ;

/* Variables and functions */
 size_t BTA_DI_NUM_MAX ; 
 int /*<<< orphan*/  BTA_FAILURE ; 
 int /*<<< orphan*/  BTA_SUCCESS ; 
 scalar_t__ SDP_SUCCESS ; 
 scalar_t__ SDP_SetLocalDiRecord (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UUID_SERVCLASS_PNP_INFORMATION ; 
 TYPE_2__ bta_dm_di_cb ; 
 int /*<<< orphan*/  bta_sys_add_uuid (int /*<<< orphan*/ ) ; 

tBTA_STATUS BTA_DmSetLocalDiRecord( tBTA_DI_RECORD *p_device_info,
                                    UINT32 *p_handle )
{
    tBTA_STATUS  status = BTA_FAILURE;

    if (bta_dm_di_cb.di_num < BTA_DI_NUM_MAX) {
        if (SDP_SetLocalDiRecord((tSDP_DI_RECORD *)p_device_info, p_handle) == SDP_SUCCESS) {
            if (!p_device_info->primary_record) {
                bta_dm_di_cb.di_handle[bta_dm_di_cb.di_num] = *p_handle;
                bta_dm_di_cb.di_num ++;
            }

            bta_sys_add_uuid(UUID_SERVCLASS_PNP_INFORMATION);
            status =  BTA_SUCCESS;
        }
    }

    return status;
}