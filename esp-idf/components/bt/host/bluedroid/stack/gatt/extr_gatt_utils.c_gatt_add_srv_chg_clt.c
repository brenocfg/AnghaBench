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
typedef  int /*<<< orphan*/  tGATTS_SRV_CHG ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_2__ {int /*<<< orphan*/  srv_chg_clt_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIXED_QUEUE_MAX_TIMEOUT ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  fixed_queue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ gatt_cb ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ osi_malloc (int /*<<< orphan*/ ) ; 

tGATTS_SRV_CHG *gatt_add_srv_chg_clt(tGATTS_SRV_CHG *p_srv_chg)
{
    tGATTS_SRV_CHG *p_buf;
    GATT_TRACE_DEBUG ("gatt_add_srv_chg_clt");
    if ((p_buf = (tGATTS_SRV_CHG *)osi_malloc((UINT16)sizeof(tGATTS_SRV_CHG))) != NULL) {
        GATT_TRACE_DEBUG ("enqueue a srv chg client");
        memcpy(p_buf, p_srv_chg, sizeof(tGATTS_SRV_CHG));
    fixed_queue_enqueue(gatt_cb.srv_chg_clt_q, p_buf, FIXED_QUEUE_MAX_TIMEOUT);
    }

    return p_buf;
}