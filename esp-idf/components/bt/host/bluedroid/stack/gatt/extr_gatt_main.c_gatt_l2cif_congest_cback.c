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
typedef  int /*<<< orphan*/  tGATT_TCB ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  gatt_channel_congestion (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gatt_find_tcb_by_cid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gatt_l2cif_congest_cback (UINT16 lcid, BOOLEAN congested)
{
    tGATT_TCB *p_tcb = gatt_find_tcb_by_cid(lcid);

    if (p_tcb != NULL) {
        gatt_channel_congestion(p_tcb, congested);
    }

}