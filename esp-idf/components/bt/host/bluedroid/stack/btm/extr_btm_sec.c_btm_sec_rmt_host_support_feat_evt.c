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
struct TYPE_3__ {int /*<<< orphan*/  sm4; } ;
typedef  TYPE_1__ tBTM_SEC_DEV_REC ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/ * BD_FEATURES ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 scalar_t__ BTM_SEC_IS_SM4_UNKNOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_SM4_KNOWN ; 
 int /*<<< orphan*/  BTM_SM4_TRUE ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_FEATURE_BYTES_PER_PAGE ; 
 scalar_t__ HCI_SSP_HOST_SUPPORTED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_TO_ARRAY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STREAM_TO_BDADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* btm_find_or_alloc_dev (int /*<<< orphan*/ ) ; 

void btm_sec_rmt_host_support_feat_evt (UINT8 *p)
{
    tBTM_SEC_DEV_REC *p_dev_rec;
    BD_ADDR         bd_addr;        /* peer address */
    BD_FEATURES     features;

    STREAM_TO_BDADDR (bd_addr, p);
    p_dev_rec = btm_find_or_alloc_dev (bd_addr);

    BTM_TRACE_EVENT ("btm_sec_rmt_host_support_feat_evt  sm4: 0x%x  p[0]: 0x%x\n", p_dev_rec->sm4, p[0]);

    if (BTM_SEC_IS_SM4_UNKNOWN(p_dev_rec->sm4)) {
        p_dev_rec->sm4 = BTM_SM4_KNOWN;
        STREAM_TO_ARRAY(features, p, HCI_FEATURE_BYTES_PER_PAGE);
        if (HCI_SSP_HOST_SUPPORTED(features)) {
            p_dev_rec->sm4 = BTM_SM4_TRUE;
        }
        BTM_TRACE_EVENT ("btm_sec_rmt_host_support_feat_evt sm4: 0x%x features[0]: 0x%x\n", p_dev_rec->sm4, features[0]);
    }
}