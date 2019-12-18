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
typedef  int /*<<< orphan*/  tBT_TRANSPORT ;
struct TYPE_4__ {int /*<<< orphan*/  bd_addr; int /*<<< orphan*/  transport; void* p_ref_data; int /*<<< orphan*/ * p_callback; scalar_t__ psm; } ;
typedef  TYPE_1__ tBTM_SEC_QUEUE_ENTRY ;
typedef  int /*<<< orphan*/  tBTM_SEC_CALLBACK ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_5__ {int /*<<< orphan*/  sec_pending_q; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXED_QUEUE_MAX_TIMEOUT ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__ btm_cb ; 
 int /*<<< orphan*/  fixed_queue_enqueue (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ osi_malloc (int) ; 

__attribute__((used)) static BOOLEAN btm_sec_queue_encrypt_request (BD_ADDR bd_addr, tBT_TRANSPORT transport,
        tBTM_SEC_CALLBACK *p_callback, void *p_ref_data)
{
    tBTM_SEC_QUEUE_ENTRY  *p_e;
    p_e = (tBTM_SEC_QUEUE_ENTRY *)osi_malloc(sizeof(tBTM_SEC_QUEUE_ENTRY) + 1);

    if (p_e) {
        p_e->psm  = 0;  /* if PSM 0, encryption request */
        p_e->p_callback  = p_callback;
        p_e->p_ref_data = (void *)(p_e + 1);
        *(UINT8 *)p_e->p_ref_data = *(UINT8 *)(p_ref_data);
        p_e->transport  = transport;
        memcpy(p_e->bd_addr, bd_addr, BD_ADDR_LEN);
        fixed_queue_enqueue(btm_cb.sec_pending_q, p_e, FIXED_QUEUE_MAX_TIMEOUT);
        return TRUE;
    }

    return FALSE;
}