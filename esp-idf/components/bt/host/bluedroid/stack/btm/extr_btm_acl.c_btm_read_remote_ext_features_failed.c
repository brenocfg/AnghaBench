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
typedef  int /*<<< orphan*/  tACL_CONN ;
typedef  size_t UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_2__ {int /*<<< orphan*/ * acl_db; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_TRACE_WARNING (char*,size_t,int /*<<< orphan*/ ) ; 
 size_t MAX_L2CAP_LINKS ; 
 TYPE_1__ btm_cb ; 
 int /*<<< orphan*/  btm_establish_continue (int /*<<< orphan*/ *) ; 
 size_t btm_handle_to_acl_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_process_remote_ext_features (int /*<<< orphan*/ *,int) ; 

void btm_read_remote_ext_features_failed (UINT8 status, UINT16 handle)
{
    tACL_CONN   *p_acl_cb;
    UINT8       acl_idx;

    BTM_TRACE_WARNING ("btm_read_remote_ext_features_failed (status 0x%02x) for handle %d\n",
                       status, handle);

    if ((acl_idx = btm_handle_to_acl_index(handle)) >= MAX_L2CAP_LINKS) {
        BTM_TRACE_ERROR("btm_read_remote_ext_features_failed handle=%d invalid\n", handle);
        return;
    }

    p_acl_cb = &btm_cb.acl_db[acl_idx];

    /* Process supported features only */
    btm_process_remote_ext_features (p_acl_cb, 1);

    /* Continue HCI connection establishment */
    btm_establish_continue (p_acl_cb);
}