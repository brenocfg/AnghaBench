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
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_L2CAP_LINKS ; 
 int /*<<< orphan*/  btsnd_hcic_host_num_xmitted_pkts (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ l2c_link_pkts_rcvd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void btu_hcif_send_host_rdy_for_data(void)
{
    UINT16      num_pkts[MAX_L2CAP_LINKS + 4];      /* 3 SCO connections */
    UINT16      handles[MAX_L2CAP_LINKS + 4];
    UINT8       num_ents;

    /* Get the L2CAP numbers */
    num_ents = l2c_link_pkts_rcvd (num_pkts, handles);

    /* Get the SCO numbers */
    /* No SCO for now ?? */

    if (num_ents) {
        btsnd_hcic_host_num_xmitted_pkts (num_ents, handles, num_pkts);
    }
}