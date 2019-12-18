#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ gatt_if; int /*<<< orphan*/  listening; } ;
typedef  TYPE_1__ tGATT_REG ;
typedef  scalar_t__ tGATT_IF ;
struct TYPE_7__ {scalar_t__* gatt_if; scalar_t__* listen_gif; int /*<<< orphan*/  remote_bda; } ;
typedef  TYPE_2__ tGATT_BG_CONN_DEV ;
typedef  size_t UINT8 ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 scalar_t__ BTM_BleUpdateAdvWhitelist (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ BTM_BleUpdateBgConnDev (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 size_t GATT_MAX_APPS ; 
 scalar_t__ TRUE ; 
 TYPE_2__* gatt_find_bg_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

BOOLEAN gatt_remove_bg_dev_from_list(tGATT_REG *p_reg, BD_ADDR bd_addr, BOOLEAN is_initiator)
{
    tGATT_IF gatt_if = p_reg->gatt_if;
    tGATT_BG_CONN_DEV   *p_dev = NULL;
    UINT8   i, j;
    BOOLEAN ret = FALSE;

    if ((p_dev = gatt_find_bg_dev(bd_addr)) == NULL) {
        return ret;
    }

    for (i = 0; i < GATT_MAX_APPS && (p_dev->gatt_if[i] > 0 || p_dev->listen_gif[i]); i ++) {
        if (is_initiator) {
            if (p_dev->gatt_if[i] == gatt_if) {
                p_dev->gatt_if[i] = 0;
                /* move all element behind one forward */
                for (j = i + 1; j < GATT_MAX_APPS; j ++) {
                    p_dev->gatt_if[j - 1] = p_dev->gatt_if[j];
                }

                if (p_dev->gatt_if[0] == 0) {
                    ret = BTM_BleUpdateBgConnDev(FALSE, p_dev->remote_bda);
                } else {
                    ret = TRUE;
                }

                break;
            }
        } else {
            if (p_dev->listen_gif[i] == gatt_if) {
                p_dev->listen_gif[i] = 0;
                p_reg->listening --;
                /* move all element behind one forward */
                for (j = i + 1; j < GATT_MAX_APPS; j ++) {
                    p_dev->listen_gif[j - 1] = p_dev->listen_gif[j];
                }

                if (p_dev->listen_gif[0] == 0) {
                    // To check, we do not support background connection, code will not be called here
                    ret = BTM_BleUpdateAdvWhitelist(FALSE, p_dev->remote_bda, 0, NULL);
                } else {
                    ret = TRUE;
                }
                break;
            }
        }
    }

    if (i != GATT_MAX_APPS && p_dev->gatt_if[0] == 0 && p_dev->listen_gif[0] == 0) {
        memset(p_dev, 0, sizeof(tGATT_BG_CONN_DEV));
    }

    return ret;
}