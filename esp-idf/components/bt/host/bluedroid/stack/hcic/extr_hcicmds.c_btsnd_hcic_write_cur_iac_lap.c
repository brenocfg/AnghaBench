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
struct TYPE_4__ {int len; scalar_t__ offset; } ;
typedef  int /*<<< orphan*/  LAP ;
typedef  TYPE_1__ BT_HDR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int HCIC_PREAMBLE_SIZE ; 
 TYPE_1__* HCI_GET_CMD_BUF (int) ; 
 int /*<<< orphan*/  HCI_WRITE_CURRENT_IAC_LAP ; 
 int LAP_LEN ; 
 int /*<<< orphan*/  LAP_TO_STREAM (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCAL_BR_EDR_CONTROLLER_ID ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int*,int) ; 
 int /*<<< orphan*/  btu_hcif_send_cmd (int /*<<< orphan*/ ,TYPE_1__*) ; 

BOOLEAN btsnd_hcic_write_cur_iac_lap (UINT8 num_cur_iac, LAP *const iac_lap)
{
    BT_HDR *p;
    UINT8 *pp;
    int i;

    if ((p = HCI_GET_CMD_BUF(1 + (LAP_LEN * num_cur_iac))) == NULL) {
        return (FALSE);
    }

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + 1 + (LAP_LEN * num_cur_iac);
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_WRITE_CURRENT_IAC_LAP);
    UINT8_TO_STREAM  (pp, p->len - HCIC_PREAMBLE_SIZE);

    UINT8_TO_STREAM (pp, num_cur_iac);

    for (i = 0; i < num_cur_iac; i++) {
        LAP_TO_STREAM (pp, iac_lap[i]);
    }

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}