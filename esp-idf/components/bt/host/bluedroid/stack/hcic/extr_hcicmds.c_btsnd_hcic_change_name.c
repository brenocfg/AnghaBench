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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_4__ {scalar_t__ offset; scalar_t__ len; } ;
typedef  TYPE_1__ BT_HDR ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  scalar_t__ BD_NAME ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_TO_STREAM (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HCIC_PARAM_SIZE_CHANGE_NAME ; 
 scalar_t__ HCIC_PREAMBLE_SIZE ; 
 int /*<<< orphan*/  HCI_CHANGE_LOCAL_NAME ; 
 TYPE_1__* HCI_GET_CMD_BUF (scalar_t__) ; 
 int /*<<< orphan*/  LOCAL_BR_EDR_CONTROLLER_ID ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  btu_hcif_send_cmd (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 

BOOLEAN btsnd_hcic_change_name (BD_NAME name)
{
    BT_HDR *p;
    UINT8 *pp;
    UINT16 len = strlen ((char *)name) + 1;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_CHANGE_NAME)) == NULL) {
        return (FALSE);
    }

    pp = (UINT8 *)(p + 1);
    memset(pp, 0, HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_CHANGE_NAME);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_CHANGE_NAME;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_CHANGE_LOCAL_NAME);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_CHANGE_NAME);

    if (len > HCIC_PARAM_SIZE_CHANGE_NAME) {
        len = HCIC_PARAM_SIZE_CHANGE_NAME;
    }

    ARRAY_TO_STREAM (pp, name, len);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}