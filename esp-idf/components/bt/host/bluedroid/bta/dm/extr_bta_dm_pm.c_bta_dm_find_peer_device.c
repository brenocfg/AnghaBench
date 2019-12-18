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
struct TYPE_6__ {int /*<<< orphan*/  peer_bdaddr; } ;
typedef  TYPE_2__ tBTA_DM_PEER_DEVICE ;
struct TYPE_5__ {int count; TYPE_2__* peer_device; } ;
struct TYPE_7__ {TYPE_1__ device_list; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  bdcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ bta_dm_cb ; 

tBTA_DM_PEER_DEVICE *bta_dm_find_peer_device(BD_ADDR peer_addr)
{
    tBTA_DM_PEER_DEVICE *p_dev = NULL;

    for (int i = 0; i < bta_dm_cb.device_list.count; i++) {
        if (!bdcmp( bta_dm_cb.device_list.peer_device[i].peer_bdaddr, peer_addr)) {
            p_dev = &bta_dm_cb.device_list.peer_device[i];
            break;
        }

    }
    return p_dev;
}