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
typedef  scalar_t__ UINT8 ;
struct TYPE_3__ {scalar_t__ offset; scalar_t__ len; } ;
typedef  TYPE_1__ BT_HDR ;

/* Variables and functions */
 scalar_t__ HCIC_PARAM_SIZE_EXT_INQ_RESP ; 
 scalar_t__ HCIC_PREAMBLE_SIZE ; 
 int /*<<< orphan*/  HCI_WRITE_EXT_INQ_RESPONSE ; 
 int /*<<< orphan*/  LOCAL_BR_EDR_CONTROLLER_ID ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  btu_hcif_send_cmd (int /*<<< orphan*/ ,TYPE_1__*) ; 

void btsnd_hcic_write_ext_inquiry_response (void *buffer, UINT8 fec_req)
{
    BT_HDR *p = (BT_HDR *)buffer;
    UINT8 *pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_EXT_INQ_RESP;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_WRITE_EXT_INQ_RESPONSE);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_EXT_INQ_RESP);

    UINT8_TO_STREAM (pp, fec_req);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
}