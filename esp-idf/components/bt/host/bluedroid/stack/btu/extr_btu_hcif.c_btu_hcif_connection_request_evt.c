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
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  DEV_CLASS ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 scalar_t__ HCI_LINK_TYPE_ACL ; 
 int /*<<< orphan*/  STREAM_TO_BDADDR (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  STREAM_TO_DEVCLASS (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  btm_sco_conn_req (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  btm_sec_conn_req (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btu_hcif_connection_request_evt (UINT8 *p)
{
    BD_ADDR     bda;
    DEV_CLASS   dc;
    UINT8       link_type;

    STREAM_TO_BDADDR   (bda, p);
    STREAM_TO_DEVCLASS (dc, p);
    STREAM_TO_UINT8    (link_type, p);
    /* Pass request to security manager to check connect filters before */
    /* passing request to l2cap */
    if (link_type == HCI_LINK_TYPE_ACL) {
#if (SMP_INCLUDED == TRUE)
        btm_sec_conn_req (bda, dc);
#endif  ///SMP_INCLUDED == TRUE
    }
#if BTM_SCO_INCLUDED == TRUE
    else {
        btm_sco_conn_req (bda, dc, link_type);
    }
#endif /* BTM_SCO_INCLUDED */
}