#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bt_mesh_model {int /*<<< orphan*/ * keys; scalar_t__ user_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ config_internal_data_t ;
struct TYPE_6__ {TYPE_1__* internal_data; int /*<<< orphan*/  op_pair; int /*<<< orphan*/  op_pair_size; struct bt_mesh_model* model; } ;
typedef  TYPE_2__ bt_mesh_config_client_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BLE_MESH_KEY_DEV ; 
 int /*<<< orphan*/  BT_DBG (char*,int) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  bt_mesh_cfg_client_mutex_new () ; 
 int /*<<< orphan*/  cfg_op_pair ; 
 TYPE_2__* cli ; 
 TYPE_1__* osi_calloc (int) ; 
 int /*<<< orphan*/  sys_slist_init (int /*<<< orphan*/ *) ; 

int bt_mesh_cfg_cli_init(struct bt_mesh_model *model, bool primary)
{
    config_internal_data_t *internal = NULL;
    bt_mesh_config_client_t *client = NULL;

    BT_DBG("primary %u", primary);

    if (!primary) {
        BT_ERR("Configuration Client only allowed in primary element");
        return -EINVAL;
    }

    if (!model) {
        BT_ERR("Configuration Client model is NULL");
        return -EINVAL;
    }

    client = (bt_mesh_config_client_t *)model->user_data;
    if (!client) {
        BT_ERR("No Configuration Client context provided");
        return -EINVAL;
    }

    /* TODO: call osi_free() when deinit function is invoked*/
    internal = osi_calloc(sizeof(config_internal_data_t));
    if (!internal) {
        BT_ERR("Allocate memory for Configuration Client internal data fail");
        return -ENOMEM;
    }

    sys_slist_init(&internal->queue);

    client->model = model;
    client->op_pair_size = ARRAY_SIZE(cfg_op_pair);
    client->op_pair = cfg_op_pair;
    client->internal_data = internal;

    cli = client;

    /* Configuration Model security is device-key based */
    model->keys[0] = BLE_MESH_KEY_DEV;

    bt_mesh_cfg_client_mutex_new();

    return 0;
}