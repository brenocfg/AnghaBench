#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  scalar_t__ BD_NAME ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 scalar_t__ BD_NAME_LEN ; 
 int /*<<< orphan*/  HCI_ERR_HOST_TIMEOUT ; 
 int /*<<< orphan*/  HCI_SUCCESS ; 
 int /*<<< orphan*/  btm_process_remote_name (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_sec_rmt_name_request_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

void btm_ble_read_remote_name_cmpl(BOOLEAN status, BD_ADDR bda, UINT16 length, char *p_name)
{
    UINT8   hci_status = HCI_SUCCESS;
    BD_NAME bd_name;

    memset(bd_name, 0, (BD_NAME_LEN + 1));
    if (length > BD_NAME_LEN) {
        length = BD_NAME_LEN;
    }
    memcpy((UINT8 *)bd_name, p_name, length);

    if ((!status) || (length == 0)) {
        hci_status = HCI_ERR_HOST_TIMEOUT;
    }

    btm_process_remote_name(bda, bd_name, length + 1, hci_status);
#if (SMP_INCLUDED == TRUE)
    btm_sec_rmt_name_request_complete (bda, (UINT8 *)p_name, hci_status);
#endif  ///SMP_INCLUDED == TRUE
}