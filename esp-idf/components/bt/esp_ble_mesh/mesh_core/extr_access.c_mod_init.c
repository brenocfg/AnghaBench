#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bt_mesh_model {scalar_t__ id; struct bt_mesh_model* model_idx; struct bt_mesh_elem* elem_idx; scalar_t__ flags; TYPE_2__* keys; TYPE_1__* pub; struct bt_mesh_elem* elem; } ;
struct bt_mesh_elem {int vnd_models; int models; } ;
struct TYPE_8__ {int elem; } ;
struct TYPE_7__ {scalar_t__ id; int /*<<< orphan*/  (* init ) (struct bt_mesh_model*,int) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  timer; struct bt_mesh_model* mod; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 TYPE_2__ BLE_MESH_KEY_UNUSED ; 
 TYPE_3__* dev_comp ; 
 int /*<<< orphan*/  k_delayed_work_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_publish ; 
 TYPE_2__* model_init ; 
 int /*<<< orphan*/  stub1 (struct bt_mesh_model*,int) ; 

__attribute__((used)) static void mod_init(struct bt_mesh_model *mod, struct bt_mesh_elem *elem,
                     bool vnd, bool primary, void *user_data)
{
    int i;

    mod->elem = elem;

    if (mod->pub) {
        mod->pub->mod = mod;
        k_delayed_work_init(&mod->pub->timer, mod_publish);
    }

    for (i = 0; i < ARRAY_SIZE(mod->keys); i++) {
        mod->keys[i] = BLE_MESH_KEY_UNUSED;
    }

    mod->flags = 0;
    mod->elem_idx = elem - dev_comp->elem;
    if (vnd) {
        mod->model_idx = mod - elem->vnd_models;
    } else {
        mod->model_idx = mod - elem->models;
    }

    if (vnd) {
        return;
    }

    for (i = 0; i < ARRAY_SIZE(model_init); i++) {
        if (model_init[i].id == mod->id) {
            model_init[i].init(mod, primary);
        }
    }
}