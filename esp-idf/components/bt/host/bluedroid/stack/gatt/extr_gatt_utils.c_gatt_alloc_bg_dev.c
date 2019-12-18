#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  remote_bda; scalar_t__ in_use; } ;
typedef  TYPE_1__ tGATT_BG_CONN_DEV ;
typedef  scalar_t__ UINT8 ;
struct TYPE_5__ {TYPE_1__* bgconn_dev; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 scalar_t__ GATT_MAX_BG_CONN_DEV ; 
 scalar_t__ TRUE ; 
 TYPE_2__ gatt_cb ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tGATT_BG_CONN_DEV *gatt_alloc_bg_dev(BD_ADDR remote_bda)
{
    tGATT_BG_CONN_DEV    *p_dev_list = &gatt_cb.bgconn_dev[0];
    UINT8   i;

    for (i = 0; i < GATT_MAX_BG_CONN_DEV; i ++, p_dev_list ++) {
        if (!p_dev_list->in_use) {
            p_dev_list->in_use = TRUE;
            memcpy(p_dev_list->remote_bda, remote_bda, BD_ADDR_LEN);

            return p_dev_list;
        }
    }
    return NULL;
}