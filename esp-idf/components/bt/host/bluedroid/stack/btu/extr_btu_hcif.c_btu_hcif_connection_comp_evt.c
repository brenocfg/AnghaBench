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
struct TYPE_4__ {int /*<<< orphan*/  bd_addr; } ;
typedef  TYPE_1__ tBTM_ESCO_DATA ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  HCID_GET_HANDLE (int /*<<< orphan*/ ) ; 
 scalar_t__ HCI_LINK_TYPE_ACL ; 
 int /*<<< orphan*/  STREAM_TO_BDADDR (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  btm_sco_connected (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  btm_sec_connected (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  l2c_link_hci_conn_comp (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void btu_hcif_connection_comp_evt (UINT8 *p)
{
    UINT8       status;
    UINT16      handle;
    BD_ADDR     bda;
    UINT8       link_type;
#if SMP_INCLUDED == TRUE
    UINT8       enc_mode;
#endif  ///SMP_INCLUDED == TRUE
#if BTM_SCO_INCLUDED == TRUE
    tBTM_ESCO_DATA  esco_data;
#endif

    STREAM_TO_UINT8    (status, p);
    STREAM_TO_UINT16   (handle, p);
    STREAM_TO_BDADDR   (bda, p);
    STREAM_TO_UINT8    (link_type, p);
#if (SMP_INCLUDED == TRUE)
    STREAM_TO_UINT8    (enc_mode, p);
#endif  ///SMP_INCLUDED == TRUE
    handle = HCID_GET_HANDLE (handle);

    if (link_type == HCI_LINK_TYPE_ACL) {
#if (SMP_INCLUDED == TRUE)
        btm_sec_connected (bda, handle, status, enc_mode);
#endif  ///SMP_INCLUDED == TRUE
        l2c_link_hci_conn_comp (status, handle, bda);
    }
#if BTM_SCO_INCLUDED == TRUE
    else {
        memset(&esco_data, 0, sizeof(tBTM_ESCO_DATA));
        /* esco_data.link_type = HCI_LINK_TYPE_SCO; already zero */
        memcpy (esco_data.bd_addr, bda, BD_ADDR_LEN);
        btm_sco_connected (status, bda, handle, &esco_data);
    }
#endif /* BTM_SCO_INCLUDED */
}