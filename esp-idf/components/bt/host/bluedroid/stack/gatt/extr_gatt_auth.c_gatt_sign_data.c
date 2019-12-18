#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int len; int /*<<< orphan*/ * value; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ tGATT_VALUE ;
struct TYPE_9__ {TYPE_4__* p_tcb; scalar_t__ p_attr_buf; } ;
typedef  TYPE_2__ tGATT_CLCB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT16 ;
struct TYPE_10__ {int payload_size; int /*<<< orphan*/  peer_bda; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int BTM_BLE_AUTH_SIGN_LEN ; 
 scalar_t__ BTM_BleDataSignature (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int GATT_AUTH_SIGN_LEN ; 
 int /*<<< orphan*/  GATT_CH_OPEN ; 
 int /*<<< orphan*/  GATT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  GATT_SEC_OK ; 
 int /*<<< orphan*/  GATT_SEC_SIGN_DATA ; 
 int /*<<< orphan*/  GATT_SIGN_CMD_WRITE ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_act_write (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_end_operation (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gatt_set_ch_state (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_set_sec_act (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 
 scalar_t__ osi_malloc (int) ; 

__attribute__((used)) static BOOLEAN gatt_sign_data (tGATT_CLCB *p_clcb)
{
    tGATT_VALUE         *p_attr = (tGATT_VALUE *)p_clcb->p_attr_buf;
    UINT8               *p_data = NULL, *p;
    UINT16              payload_size = p_clcb->p_tcb->payload_size;
    BOOLEAN             status = FALSE;
    UINT8                *p_signature;

    /* do not need to mark channel securoty activity for data signing */
    gatt_set_sec_act(p_clcb->p_tcb, GATT_SEC_OK);

    p_data = (UINT8 *)osi_malloc((UINT16)(p_attr->len + 3)); /* 3 = 2 byte handle + opcode */

    if (p_data != NULL) {
        p = p_data;
        UINT8_TO_STREAM(p, GATT_SIGN_CMD_WRITE);
        UINT16_TO_STREAM(p, p_attr->handle);
        ARRAY_TO_STREAM(p, p_attr->value, p_attr->len);

        /* sign data length should be attribulte value length plus 2B handle + 1B op code */
        if ((payload_size - GATT_AUTH_SIGN_LEN - 3) < p_attr->len) {
            p_attr->len = payload_size - GATT_AUTH_SIGN_LEN - 3;
        }

        p_signature = p_attr->value + p_attr->len;
        if (BTM_BleDataSignature(p_clcb->p_tcb->peer_bda,
                                 p_data,
                                 (UINT16)(p_attr->len + 3), /* 3 = 2 byte handle + opcode */
                                 p_signature)) {
            p_attr->len += BTM_BLE_AUTH_SIGN_LEN;
            gatt_set_ch_state(p_clcb->p_tcb, GATT_CH_OPEN);
#if (GATTC_INCLUDED == TRUE)
            gatt_act_write(p_clcb, GATT_SEC_SIGN_DATA);
#endif  ///GATTC_INCLUDED == TRUE
        } else {
            gatt_end_operation(p_clcb, GATT_INTERNAL_ERROR, NULL);
        }

        osi_free(p_data);
    }

    return status;
}