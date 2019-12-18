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
typedef  size_t uint32_t ;
struct TYPE_4__ {size_t props_count; TYPE_1__** props; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_2__* local_ctrl_inst_ctx ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int esp_local_ctrl_get_property_index(const char *name)
{
    if (!local_ctrl_inst_ctx || !name) {
        return -1;
    }

    /* Iterate through all properties one by one
     * and find the one with matching name */
    for (uint32_t i = 0; i < local_ctrl_inst_ctx->props_count; i++) {
        if (strcmp(local_ctrl_inst_ctx->props[i]->name, name) == 0) {
            return i;
        }
    }
    return -1;
}