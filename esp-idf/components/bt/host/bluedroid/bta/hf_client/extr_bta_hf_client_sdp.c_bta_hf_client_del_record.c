#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_HF_CLIENT_DATA ;
struct TYPE_2__ {scalar_t__ sdp_handle; int /*<<< orphan*/  scn; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  BTM_FreeSCN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_SEC_SERVICE_HF_HANDSFREE ; 
 int /*<<< orphan*/  BTM_SecClrService (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDP_DeleteRecord (scalar_t__) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UUID_SERVCLASS_HF_HANDSFREE ; 
 TYPE_1__ bta_hf_client_cb ; 
 int /*<<< orphan*/  bta_sys_remove_uuid (int /*<<< orphan*/ ) ; 

void bta_hf_client_del_record(tBTA_HF_CLIENT_DATA *p_data)
{
    UNUSED(p_data);

    APPL_TRACE_DEBUG("bta_hf_client_del_record");

    if (bta_hf_client_cb.sdp_handle != 0) {
        SDP_DeleteRecord(bta_hf_client_cb.sdp_handle);
        bta_hf_client_cb.sdp_handle = 0;
        BTM_FreeSCN(bta_hf_client_cb.scn);
        BTM_SecClrService(BTM_SEC_SERVICE_HF_HANDSFREE);
        bta_sys_remove_uuid(UUID_SERVCLASS_HF_HANDSFREE);
    }
}