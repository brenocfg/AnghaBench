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
struct TYPE_3__ {int /*<<< orphan*/  bda; scalar_t__ srv_changed; } ;
typedef  TYPE_1__ tGATTS_SRV_CHG ;

/* Variables and functions */
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*,scalar_t__) ; 
 int /*<<< orphan*/  gatt_send_srv_chg_ind (int /*<<< orphan*/ ) ; 

void gatt_chk_srv_chg(tGATTS_SRV_CHG *p_srv_chg_clt)
{
    GATT_TRACE_DEBUG("gatt_chk_srv_chg srv_changed=%d", p_srv_chg_clt->srv_changed );

    if (p_srv_chg_clt->srv_changed) {
        gatt_send_srv_chg_ind(p_srv_chg_clt->bda);
    }
}