#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_SYS_CONN_CBACK ;
typedef  size_t UINT8 ;
struct TYPE_3__ {size_t* id; int /*<<< orphan*/ ** p_coll_cback; } ;
struct TYPE_4__ {TYPE_1__ colli_reg; } ;

/* Variables and functions */
 size_t MAX_COLLISION_REG ; 
 TYPE_2__ bta_sys_cb ; 

void bta_sys_collision_register(UINT8 bta_id, tBTA_SYS_CONN_CBACK *p_cback)
{
    UINT8 index;

    for (index = 0; index < MAX_COLLISION_REG; index++) {
        if ((bta_sys_cb.colli_reg.id[index] == bta_id) ||
                (bta_sys_cb.colli_reg.id[index] == 0)) {
            bta_sys_cb.colli_reg.id[index] = bta_id;
            bta_sys_cb.colli_reg.p_coll_cback[index] = p_cback;
            return;
        }
    }
}