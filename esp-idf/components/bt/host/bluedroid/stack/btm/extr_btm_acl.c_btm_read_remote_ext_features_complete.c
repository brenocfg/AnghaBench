#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * peer_lmp_features; } ;
typedef  TYPE_1__ tACL_CONN ;
typedef  size_t UINT8 ;
typedef  size_t UINT16 ;
struct TYPE_6__ {TYPE_1__* acl_db; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,...) ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*,size_t) ; 
 size_t HCI_EXT_FEATURES_PAGE_MAX ; 
 int /*<<< orphan*/  HCI_FEATURE_BYTES_PER_PAGE ; 
 size_t MAX_L2CAP_LINKS ; 
 int /*<<< orphan*/  STREAM_TO_ARRAY (int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (size_t,size_t*) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (size_t,size_t*) ; 
 TYPE_4__ btm_cb ; 
 int /*<<< orphan*/  btm_establish_continue (TYPE_1__*) ; 
 size_t btm_handle_to_acl_index (size_t) ; 
 int /*<<< orphan*/  btm_process_remote_ext_features (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  btm_read_remote_ext_features (size_t,size_t) ; 

void btm_read_remote_ext_features_complete (UINT8 *p)
{
    tACL_CONN   *p_acl_cb;
    UINT8       page_num, max_page;
    UINT16      handle;
    UINT8       acl_idx;

    BTM_TRACE_DEBUG ("btm_read_remote_ext_features_complete\n");

    ++p;
    STREAM_TO_UINT16 (handle, p);
    STREAM_TO_UINT8  (page_num, p);
    STREAM_TO_UINT8  (max_page, p);

    /* Validate parameters */
    if ((acl_idx = btm_handle_to_acl_index(handle)) >= MAX_L2CAP_LINKS) {
        BTM_TRACE_ERROR("btm_read_remote_ext_features_complete handle=%d invalid\n", handle);
        return;
    }

    if (max_page > HCI_EXT_FEATURES_PAGE_MAX) {
        BTM_TRACE_ERROR("btm_read_remote_ext_features_complete page=%d unknown", max_page);
        return;
    }

    p_acl_cb = &btm_cb.acl_db[acl_idx];

    /* Copy the received features page */
    STREAM_TO_ARRAY(p_acl_cb->peer_lmp_features[page_num], p, HCI_FEATURE_BYTES_PER_PAGE);

    /* If there is the next remote features page and
     * we have space to keep this page data - read this page */
    if ((page_num < max_page) && (page_num < HCI_EXT_FEATURES_PAGE_MAX)) {
        page_num++;
        BTM_TRACE_DEBUG("BTM reads next remote extended features page (%d)\n", page_num);
        btm_read_remote_ext_features (handle, page_num);
        return;
    }

    /* Reading of remote feature pages is complete */
    BTM_TRACE_DEBUG("BTM reached last remote extended features page (%d)\n", page_num);

    /* Process the pages */
    btm_process_remote_ext_features (p_acl_cb, (UINT8) (page_num + 1));

    /* Continue with HCI connection establishment */
    btm_establish_continue (p_acl_cb);
}