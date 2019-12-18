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
struct net_buf_simple {int dummy; } ;
struct bt_mesh_model {struct bt_mesh_health_srv* user_data; } ;
struct TYPE_2__ {scalar_t__* curr_faults; scalar_t__* reg_faults; } ;
struct bt_mesh_health_srv {TYPE_1__ test; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ HEALTH_NO_FAULT ; 
 int /*<<< orphan*/  net_buf_simple_add_u8 (struct net_buf_simple*,scalar_t__) ; 
 scalar_t__ net_buf_simple_tailroom (struct net_buf_simple*) ; 

__attribute__((used)) static void health_get_fault_value(struct bt_mesh_model *model,
                                   struct net_buf_simple *msg,
                                   bool current)
{
    struct bt_mesh_health_srv *srv = model->user_data;
    size_t array_size;
    size_t i;

    array_size = current ? ARRAY_SIZE(srv->test.curr_faults) : ARRAY_SIZE(srv->test.reg_faults);

    for (i = 0U; i < array_size; i++) {
        if (net_buf_simple_tailroom(msg) == 0) {
            return;
        }

        u8_t fault = current ? srv->test.curr_faults[i] : srv->test.reg_faults[i];
        if (fault != HEALTH_NO_FAULT) {
            net_buf_simple_add_u8(msg, fault);
        }
    }
}