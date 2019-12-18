#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_14__ {scalar_t__ size; } ;
typedef  TYPE_3__ esp_local_ctrl_prop_val_t ;
struct TYPE_15__ {scalar_t__ size; int /*<<< orphan*/  ctx; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
typedef  TYPE_4__ esp_local_ctrl_prop_t ;
struct TYPE_16__ {int /*<<< orphan*/  usr_ctx; int /*<<< orphan*/  (* set_prop_values ) (size_t,TYPE_4__*,TYPE_3__ const*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_5__ esp_local_ctrl_handlers_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_13__ {TYPE_5__ handlers; } ;
struct TYPE_17__ {size_t props_count; TYPE_2__ config; TYPE_1__** props; } ;
struct TYPE_12__ {scalar_t__ size; int /*<<< orphan*/  ctx; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_4__* calloc (size_t,int) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 TYPE_8__* local_ctrl_inst_ctx ; 
 int /*<<< orphan*/  stub1 (size_t,TYPE_4__*,TYPE_3__ const*,int /*<<< orphan*/ ) ; 

esp_err_t esp_local_ctrl_set_prop_values(size_t total_indices, uint32_t *indices,
                                         const esp_local_ctrl_prop_val_t *values)
{
   if (!local_ctrl_inst_ctx) {
        ESP_LOGE(TAG, "Service not running");
        return ESP_ERR_INVALID_STATE;
    }
    if (!indices || !values) {
        return ESP_ERR_INVALID_ARG;
    }

    esp_local_ctrl_prop_t *props = calloc(total_indices,
                                          sizeof(esp_local_ctrl_prop_t));
    if (!props) {
        ESP_LOGE(TAG, "Unable to allocate memory for properties array");
        return ESP_ERR_NO_MEM;
    }
    for (size_t i = 0; i < total_indices; i++) {
        if (indices[i] >= local_ctrl_inst_ctx->props_count) {
            ESP_LOGE(TAG, "Invalid property index %d", indices[i]);
            free(props);
            return ESP_ERR_INVALID_ARG;
        }

        /* Properties with fixed sizes need to be checked */
        if ((local_ctrl_inst_ctx->props[indices[i]]->size != values[i].size) &&
            (local_ctrl_inst_ctx->props[indices[i]]->size != 0)) {
            ESP_LOGE(TAG, "Invalid property size %d. Expected %d",
                     values[i].size, local_ctrl_inst_ctx->props[indices[i]]->size);
            free(props);
            return ESP_ERR_INVALID_ARG;
        }

        props[i].name  = local_ctrl_inst_ctx->props[indices[i]]->name;
        props[i].type  = local_ctrl_inst_ctx->props[indices[i]]->type;
        props[i].flags = local_ctrl_inst_ctx->props[indices[i]]->flags;
        props[i].size  = local_ctrl_inst_ctx->props[indices[i]]->size;
        props[i].ctx   = local_ctrl_inst_ctx->props[indices[i]]->ctx;
    }

    esp_local_ctrl_handlers_t *h = &local_ctrl_inst_ctx->config.handlers;
    esp_err_t ret = h->set_prop_values(total_indices, props, values, h->usr_ctx);

    free(props);
    return ret;
}