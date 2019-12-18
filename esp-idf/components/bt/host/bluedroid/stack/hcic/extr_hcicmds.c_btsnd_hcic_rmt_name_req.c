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
typedef  TYPE_1__ BT_HDR ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BDADDR_TO_STREAM (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HCIC_PARAM_SIZE_RMT_NAME_REQ ; 
 scalar_t__ HCIC_PREAMBLE_SIZE ; 
 TYPE_1__* HCI_GET_CMD_BUF (scalar_t__) ; 
 int /*<<< orphan*/  HCI_RMT_NAME_REQUEST ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  btm_acl_paging (TYPE_1__*,int /*<<< orphan*/ ) ; 

BOOLEAN btsnd_hcic_rmt_name_req (BD_ADDR bd_addr, UINT8 page_scan_rep_mode,
                                 UINT8 page_scan_mode, UINT16 clock_offset)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_RMT_NAME_REQ)) == NULL) {
        return (FALSE);
    }

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_RMT_NAME_REQ;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_RMT_NAME_REQUEST);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_RMT_NAME_REQ);

    BDADDR_TO_STREAM (pp, bd_addr);
    UINT8_TO_STREAM  (pp, page_scan_rep_mode);
    UINT8_TO_STREAM  (pp, page_scan_mode);
    UINT16_TO_STREAM (pp, clock_offset);
#if (SMP_INCLUDED == TRUE && CLASSIC_BT_INCLUDED == TRUE)
    btm_acl_paging (p, bd_addr);
#endif  ///SMP_INCLUDED == TRUE && CLASSIC_BT_INCLUDED == TRUE
    return (TRUE);
}