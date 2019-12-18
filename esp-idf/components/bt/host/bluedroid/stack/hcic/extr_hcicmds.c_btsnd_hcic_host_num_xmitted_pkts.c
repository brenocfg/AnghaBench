#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_4__ {int len; scalar_t__ offset; } ;
typedef  TYPE_1__ BT_HDR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int HCIC_PREAMBLE_SIZE ; 
 TYPE_1__* HCI_GET_CMD_BUF (int) ; 
 int /*<<< orphan*/  HCI_HOST_NUM_PACKETS_DONE ; 
 int /*<<< orphan*/  LOCAL_BR_EDR_CONTROLLER_ID ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int*,int) ; 
 int /*<<< orphan*/  btu_hcif_send_cmd (int /*<<< orphan*/ ,TYPE_1__*) ; 

BOOLEAN btsnd_hcic_host_num_xmitted_pkts (UINT8 num_handles, UINT16 *handle,
        UINT16 *num_pkts)
{
    BT_HDR *p;
    UINT8 *pp;
    int j;

    if ((p = HCI_GET_CMD_BUF(1 + (num_handles * 4))) == NULL) {
        return (FALSE);
    }

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + 1 + (num_handles * 4);
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_HOST_NUM_PACKETS_DONE);
    UINT8_TO_STREAM  (pp, p->len - HCIC_PREAMBLE_SIZE);

    UINT8_TO_STREAM (pp, num_handles);

    for (j = 0; j < num_handles; j++) {
        UINT16_TO_STREAM (pp, handle[j]);
        UINT16_TO_STREAM (pp, num_pkts[j]);
    }

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}