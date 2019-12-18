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
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  HCID_GET_HANDLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btm_sco_removed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_sec_disconnected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2c_link_hci_disc_comp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btu_hcif_disconnection_comp_evt (UINT8 *p)
{
    UINT16  handle;
    UINT8   reason;

    ++p;
    STREAM_TO_UINT16 (handle, p);
    STREAM_TO_UINT8  (reason, p);

    handle = HCID_GET_HANDLE (handle);

#if BTM_SCO_INCLUDED == TRUE
    /* If L2CAP doesn't know about it, send it to SCO */
    if (!l2c_link_hci_disc_comp (handle, reason)) {
        btm_sco_removed (handle, reason);
    }
#else
    l2c_link_hci_disc_comp (handle, reason);
#endif /* BTM_SCO_INCLUDED */
#if (SMP_INCLUDED == TRUE)
    /* Notify security manager */
    btm_sec_disconnected (handle, reason);
#endif  ///SMP_INCLUDED == TRUE
}