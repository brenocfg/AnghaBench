#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8_t ;
typedef  scalar_t__ u16_t ;
struct TYPE_3__ {scalar_t__ addr; int /*<<< orphan*/ * uuid; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  BT_DBG (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  BT_WARN (char*,scalar_t__) ; 
 int /*<<< orphan*/  bt_hex (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* labels ; 

u8_t *bt_mesh_label_uuid_get(u16_t addr)
{
    int i;

    BT_DBG("addr 0x%04x", addr);

    for (i = 0; i < ARRAY_SIZE(labels); i++) {
        if (labels[i].addr == addr) {
            BT_DBG("Found Label UUID for 0x%04x: %s", addr,
                   bt_hex(labels[i].uuid, 16));
            return labels[i].uuid;
        }
    }

    BT_WARN("No matching Label UUID for 0x%04x", addr);

    return NULL;
}