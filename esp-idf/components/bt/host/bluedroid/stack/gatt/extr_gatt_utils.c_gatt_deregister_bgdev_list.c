#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ listening; } ;
typedef  TYPE_1__ tGATT_REG ;
typedef  scalar_t__ tGATT_IF ;
struct TYPE_6__ {scalar_t__* gatt_if; scalar_t__* listen_gif; int /*<<< orphan*/  remote_bda; scalar_t__ in_use; } ;
typedef  TYPE_2__ tGATT_BG_CONN_DEV ;
typedef  scalar_t__ UINT8 ;
struct TYPE_7__ {TYPE_2__* bgconn_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BleUpdateAdvWhitelist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BTM_BleUpdateBgConnDev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GATT_MAX_APPS ; 
 scalar_t__ GATT_MAX_BG_CONN_DEV ; 
 TYPE_4__ gatt_cb ; 
 TYPE_1__* gatt_get_regcb (scalar_t__) ; 

void gatt_deregister_bgdev_list(tGATT_IF gatt_if)
{
    tGATT_BG_CONN_DEV    *p_dev_list = &gatt_cb.bgconn_dev[0];
    UINT8 i , j, k;
    tGATT_REG       *p_reg = gatt_get_regcb(gatt_if);

    /* update the BG conn device list */
    for (i = 0 ; i < GATT_MAX_BG_CONN_DEV; i ++, p_dev_list ++ ) {
        if (p_dev_list->in_use) {
            for (j = 0; j < GATT_MAX_APPS; j ++) {
                if (p_dev_list->gatt_if[j] == 0 && p_dev_list->listen_gif[j] == 0) {
                    break;
                }

                if (p_dev_list->gatt_if[j] == gatt_if) {
                    for (k = j + 1; k < GATT_MAX_APPS; k ++) {
                        p_dev_list->gatt_if[k - 1] = p_dev_list->gatt_if[k];
                    }

                    if (p_dev_list->gatt_if[0] == 0) {
                        BTM_BleUpdateBgConnDev(FALSE, p_dev_list->remote_bda);
                    }
                }

                if (p_dev_list->listen_gif[j] == gatt_if) {
                    p_dev_list->listen_gif[j] = 0;

                    if (p_reg != NULL && p_reg->listening > 0) {
                        p_reg->listening --;
                    }

                    /* move all element behind one forward */
                    for (k = j + 1; k < GATT_MAX_APPS; k ++) {
                        p_dev_list->listen_gif[k - 1] = p_dev_list->listen_gif[k];
                    }

                    if (p_dev_list->listen_gif[0] == 0) {
                        // To check, we do not support background connection, code will not be called here
                        BTM_BleUpdateAdvWhitelist(FALSE, p_dev_list->remote_bda, 0, NULL);
                    }
                }
            }
        }
    }
}