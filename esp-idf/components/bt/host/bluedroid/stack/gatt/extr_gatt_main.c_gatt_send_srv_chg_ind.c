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
typedef  int /*<<< orphan*/  tGATT_STATUS ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_2__ {scalar_t__ handle_of_h_r; } ;
typedef  int /*<<< orphan*/ * BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  GATTS_HandleValueIndication (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GATT_ERROR ; 
 int /*<<< orphan*/  GATT_INVALID_CONN_ID ; 
 int /*<<< orphan*/  GATT_NOT_FOUND ; 
 int GATT_SIZE_OF_SRV_CHG_HNDL_RANGE ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (int /*<<< orphan*/ *,int) ; 
 TYPE_1__ gatt_cb ; 
 int /*<<< orphan*/  gatt_profile_find_conn_id_by_bd_addr (int /*<<< orphan*/ *) ; 

tGATT_STATUS gatt_send_srv_chg_ind (BD_ADDR peer_bda)
{
    UINT8   handle_range[GATT_SIZE_OF_SRV_CHG_HNDL_RANGE];
    UINT8   *p = handle_range;
    UINT16  conn_id;
    tGATT_STATUS  status = GATT_ERROR;
    GATT_TRACE_DEBUG("gatt_send_srv_chg_ind");

    if (gatt_cb.handle_of_h_r) {
        if ((conn_id = gatt_profile_find_conn_id_by_bd_addr(peer_bda)) != GATT_INVALID_CONN_ID) {
            UINT16_TO_STREAM (p, 1);
            UINT16_TO_STREAM (p, 0xFFFF);
            status = GATTS_HandleValueIndication (conn_id,
                                         gatt_cb.handle_of_h_r,
                                         GATT_SIZE_OF_SRV_CHG_HNDL_RANGE,
                                         handle_range);
        } else {
            status = GATT_NOT_FOUND;
            GATT_TRACE_ERROR("Unable to find conn_id for  %02x%02x%02x%02x%02x%02x ",
                             peer_bda[0], peer_bda[1],  peer_bda[2], peer_bda[3], peer_bda[4], peer_bda[5]);
        }
    }
    return status;
}