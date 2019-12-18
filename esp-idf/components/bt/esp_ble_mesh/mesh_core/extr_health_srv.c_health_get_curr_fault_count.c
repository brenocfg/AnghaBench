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
typedef  scalar_t__ u8_t ;
struct bt_mesh_model {struct bt_mesh_health_srv* user_data; } ;
struct TYPE_2__ {scalar_t__* curr_faults; } ;
struct bt_mesh_health_srv {TYPE_1__ test; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ HEALTH_NO_FAULT ; 

__attribute__((used)) static u8_t health_get_curr_fault_count(struct bt_mesh_model *model)
{
    struct bt_mesh_health_srv *srv = model->user_data;
    u8_t count = 0;
    size_t i;

    for (i = 0U; i < ARRAY_SIZE(srv->test.curr_faults); i++) {
        if (srv->test.curr_faults[i] != HEALTH_NO_FAULT) {
            count++;
        }
    }

    return count;
}