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
typedef  scalar_t__ u16_t ;
struct bt_mesh_model {scalar_t__* keys; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 

__attribute__((used)) static bool model_has_key(struct bt_mesh_model *mod, u16_t key)
{
    int i;

    for (i = 0; i < ARRAY_SIZE(mod->keys); i++) {
        if (mod->keys[i] == key) {
            return true;
        }
    }

    return false;
}