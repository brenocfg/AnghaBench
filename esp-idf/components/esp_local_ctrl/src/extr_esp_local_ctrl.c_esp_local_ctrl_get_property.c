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
typedef  int /*<<< orphan*/  esp_local_ctrl_prop_t ;
struct TYPE_2__ {int /*<<< orphan*/  const** props; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  TAG ; 
 int esp_local_ctrl_get_property_index (char const*) ; 
 TYPE_1__* local_ctrl_inst_ctx ; 

const esp_local_ctrl_prop_t *esp_local_ctrl_get_property(const char *name)
{
    int idx = esp_local_ctrl_get_property_index(name);
    if (idx < 0) {
        ESP_LOGE(TAG, "Property %s not found", name);
        return NULL;
    }

    return local_ctrl_inst_ctx->props[idx];
}