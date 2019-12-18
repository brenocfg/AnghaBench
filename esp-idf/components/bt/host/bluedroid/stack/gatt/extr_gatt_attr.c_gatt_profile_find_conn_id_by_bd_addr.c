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
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_2__ {int /*<<< orphan*/  gatt_if; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BT_TRANSPORT_LE ; 
 int /*<<< orphan*/  GATT_GetConnIdIfConnected (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GATT_INVALID_CONN_ID ; 
 TYPE_1__ gatt_cb ; 

UINT16 gatt_profile_find_conn_id_by_bd_addr(BD_ADDR remote_bda)
{
    UINT16 conn_id = GATT_INVALID_CONN_ID;
    GATT_GetConnIdIfConnected (gatt_cb.gatt_if, remote_bda, &conn_id, BT_TRANSPORT_LE);
    return conn_id;
}