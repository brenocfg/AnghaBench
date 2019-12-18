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
typedef  void* UINT16 ;
struct TYPE_4__ {void* len; scalar_t__ offset; } ;
typedef  TYPE_1__ BT_HDR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_TO_STREAM (int*,int*,int) ; 
 int /*<<< orphan*/  BDADDR_TO_STREAM (int*,int*) ; 
 int BD_ADDR_LEN ; 
 int /*<<< orphan*/  DEVCLASS_TO_STREAM (int*,int*) ; 
 int DEV_CLASS_LEN ; 
 int /*<<< orphan*/  FALSE ; 
 int HCIC_PREAMBLE_SIZE ; 
 int HCI_FILTER_COND_BD_ADDR ; 
 int HCI_FILTER_COND_DEVICE_CLASS ; 
 TYPE_1__* HCI_GET_CMD_BUF (int) ; 
 int /*<<< orphan*/  HCI_SET_EVENT_FILTER ; 
 int /*<<< orphan*/  LOCAL_BR_EDR_CONTROLLER_ID ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int*,int) ; 
 int /*<<< orphan*/  btu_hcif_send_cmd (int /*<<< orphan*/ ,TYPE_1__*) ; 

BOOLEAN btsnd_hcic_set_event_filter (UINT8 filt_type, UINT8 filt_cond_type,
                                     UINT8 *filt_cond, UINT8 filt_cond_len)
{
    BT_HDR *p;
    UINT8 *pp;

    /* Use buffer large enough to hold all sizes in this command */
    if ((p = HCI_GET_CMD_BUF(2 + filt_cond_len)) == NULL) {
        return (FALSE);
    }

    pp = (UINT8 *)(p + 1);

    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_SET_EVENT_FILTER);

    if (filt_type) {
        p->len = (UINT16)(HCIC_PREAMBLE_SIZE + 2 + filt_cond_len);
        UINT8_TO_STREAM (pp, (UINT8)(2 + filt_cond_len));

        UINT8_TO_STREAM (pp, filt_type);
        UINT8_TO_STREAM (pp, filt_cond_type);

        if (filt_cond_type == HCI_FILTER_COND_DEVICE_CLASS) {
            DEVCLASS_TO_STREAM (pp, filt_cond);
            filt_cond += DEV_CLASS_LEN;
            DEVCLASS_TO_STREAM (pp, filt_cond);
            filt_cond += DEV_CLASS_LEN;

            filt_cond_len -= (2 * DEV_CLASS_LEN);
        } else if (filt_cond_type == HCI_FILTER_COND_BD_ADDR) {
            BDADDR_TO_STREAM (pp, filt_cond);
            filt_cond += BD_ADDR_LEN;

            filt_cond_len -= BD_ADDR_LEN;
        }

        if (filt_cond_len) {
            ARRAY_TO_STREAM (pp, filt_cond, filt_cond_len);
        }
    } else {
        p->len = (UINT16)(HCIC_PREAMBLE_SIZE + 1);
        UINT8_TO_STREAM (pp, 1);

        UINT8_TO_STREAM (pp, filt_type);
    }

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}