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
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_4__ {scalar_t__ offset; scalar_t__ len; } ;
typedef  int /*<<< orphan*/  LAP ;
typedef  TYPE_1__ BT_HDR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HCIC_PARAM_SIZE_PER_INQ_MODE ; 
 scalar_t__ HCIC_PREAMBLE_SIZE ; 
 TYPE_1__* HCI_GET_CMD_BUF (scalar_t__) ; 
 int /*<<< orphan*/  HCI_PERIODIC_INQUIRY_MODE ; 
 int /*<<< orphan*/  LAP_TO_STREAM (scalar_t__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  LOCAL_BR_EDR_CONTROLLER_ID ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  btu_hcif_send_cmd (int /*<<< orphan*/ ,TYPE_1__*) ; 

BOOLEAN btsnd_hcic_per_inq_mode (UINT16 max_period, UINT16 min_period,
                                 const LAP inq_lap, UINT8 duration, UINT8 response_cnt)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_PER_INQ_MODE)) == NULL) {
        return (FALSE);
    }

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_PER_INQ_MODE;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_PERIODIC_INQUIRY_MODE);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_PER_INQ_MODE);

    UINT16_TO_STREAM (pp, max_period);
    UINT16_TO_STREAM (pp, min_period);
    LAP_TO_STREAM    (pp, inq_lap);
    UINT8_TO_STREAM  (pp, duration);
    UINT8_TO_STREAM  (pp, response_cnt);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID, p);
    return (TRUE);
}