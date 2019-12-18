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
struct TYPE_3__ {scalar_t__ conn_state; } ;
typedef  TYPE_1__ tBTA_DM_PEER_DEVICE ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 scalar_t__ BTA_DM_CONNECTED ; 
 TYPE_1__* bta_dm_find_peer_device (int /*<<< orphan*/ ) ; 

UINT16 BTA_DmGetConnectionState( BD_ADDR bd_addr )
{
    tBTA_DM_PEER_DEVICE *p_dev = bta_dm_find_peer_device(bd_addr);
    return (p_dev && p_dev->conn_state == BTA_DM_CONNECTED);
}