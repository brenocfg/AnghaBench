#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dev_class; int /*<<< orphan*/  bd_addr; } ;
typedef  TYPE_1__ tBTM_SEC_DEV_REC ;
struct TYPE_5__ {int* connecting_bda; int* connecting_dc; void* paging; int /*<<< orphan*/  page_queue; scalar_t__ discing; } ;
typedef  int /*<<< orphan*/  BT_HDR ;
typedef  int* BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  BTM_ACL_IS_CONNECTED (int*) ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,int,int,...) ; 
 int /*<<< orphan*/  DEV_CLASS_LEN ; 
 int /*<<< orphan*/  FIXED_QUEUE_MAX_TIMEOUT ; 
 int /*<<< orphan*/  LOCAL_BR_EDR_CONTROLLER_ID ; 
 void* TRUE ; 
 TYPE_3__ btm_cb ; 
 TYPE_1__* btm_find_or_alloc_dev (int*) ; 
 int /*<<< orphan*/  btu_hcif_send_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fixed_queue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void  btm_acl_paging (BT_HDR *p, BD_ADDR bda)
{
    tBTM_SEC_DEV_REC *p_dev_rec;

    BTM_TRACE_DEBUG ("btm_acl_paging discing:%d, paging:%d BDA: %06x%06x\n",
                     btm_cb.discing, btm_cb.paging,
                     (bda[0] << 16) + (bda[1] << 8) + bda[2], (bda[3] << 16) + (bda[4] << 8) + bda[5]);
    if (btm_cb.discing) {
        btm_cb.paging = TRUE;
        fixed_queue_enqueue(btm_cb.page_queue, p, FIXED_QUEUE_MAX_TIMEOUT);
    } else {
        if (!BTM_ACL_IS_CONNECTED (bda)) {
            BTM_TRACE_DEBUG ("connecting_bda: %06x%06x\n",
                             (btm_cb.connecting_bda[0] << 16) + (btm_cb.connecting_bda[1] << 8) +
                             btm_cb.connecting_bda[2],
                             (btm_cb.connecting_bda[3] << 16) + (btm_cb.connecting_bda[4] << 8) +
                             btm_cb.connecting_bda[5]);
            if (btm_cb.paging &&
                    memcmp (bda, btm_cb.connecting_bda, BD_ADDR_LEN) != 0) {
                fixed_queue_enqueue(btm_cb.page_queue, p, FIXED_QUEUE_MAX_TIMEOUT);
            } else {
                p_dev_rec = btm_find_or_alloc_dev (bda);
                memcpy (btm_cb.connecting_bda, p_dev_rec->bd_addr,   BD_ADDR_LEN);
                memcpy (btm_cb.connecting_dc,  p_dev_rec->dev_class, DEV_CLASS_LEN);

                btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID, p);
            }

            btm_cb.paging = TRUE;
        } else { /* ACL is already up */
            btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID, p);
        }
    }
}