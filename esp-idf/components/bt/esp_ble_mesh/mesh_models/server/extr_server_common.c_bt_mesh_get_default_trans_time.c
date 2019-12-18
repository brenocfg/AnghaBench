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
typedef  int /*<<< orphan*/  u8_t ;
typedef  scalar_t__ u16_t ;
struct bt_mesh_model {scalar_t__ user_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  trans_time; } ;
struct bt_mesh_gen_def_trans_time_srv {TYPE_1__ state; } ;
struct bt_mesh_elem {scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_MESH_MODEL_ID_GEN_DEF_TRANS_TIME_SRV ; 
 int /*<<< orphan*/  INSTANTANEOUS_TRANS_TIME ; 
 struct bt_mesh_elem* bt_mesh_elem_find (scalar_t__) ; 
 struct bt_mesh_elem* bt_mesh_model_elem (struct bt_mesh_model*) ; 
 struct bt_mesh_model* bt_mesh_model_find (struct bt_mesh_elem*,int /*<<< orphan*/ ) ; 
 scalar_t__ bt_mesh_primary_addr () ; 

u8_t bt_mesh_get_default_trans_time(struct bt_mesh_model *model)
{
    /**
     * 1. If a Generic Default Transition Time Server model is present on the
     *    main element of the model, that model instance shall be used.
     * 2. If a Generic Default Transition Time Server model is not present on
     *    the main element of the model, then the Generic Default Transition
     *    Time Server model instance that is present on the element with the
     *    largest address that is smaller than the address of the main element
     *    of the node shall be used; if no model instance is present on any
     *    element with an address smaller than the address of the main element,
     *    then the Generic Default Transition Time Server is not supported.
     */
    struct bt_mesh_elem *element = bt_mesh_model_elem(model);
    struct bt_mesh_gen_def_trans_time_srv *state = NULL;
    u16_t primary_addr = bt_mesh_primary_addr();
    struct bt_mesh_model *srv = NULL;

    for (u16_t addr = element->addr; addr >= primary_addr; addr--) {
        element = bt_mesh_elem_find(addr);
        if (element) {
            srv = bt_mesh_model_find(element, BLE_MESH_MODEL_ID_GEN_DEF_TRANS_TIME_SRV);
            if (srv) {
                state = (struct bt_mesh_gen_def_trans_time_srv *)srv->user_data;
                if (state) {
                    return state->state.trans_time;
                }
            }
        }
    }

    return INSTANTANEOUS_TRANS_TIME;
}