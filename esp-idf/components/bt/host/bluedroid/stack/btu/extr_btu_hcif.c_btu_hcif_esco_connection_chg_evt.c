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
 int /*<<< orphan*/  STREAM_TO_UINT16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btm_esco_proc_conn_chg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btu_hcif_esco_connection_chg_evt (UINT8 *p)
{
#if BTM_SCO_INCLUDED == TRUE
    UINT16  handle;
    UINT16  tx_pkt_len;
    UINT16  rx_pkt_len;
    UINT8   status;
    UINT8   tx_interval;
    UINT8   retrans_window;

    STREAM_TO_UINT8 (status, p);
    STREAM_TO_UINT16 (handle, p);

    STREAM_TO_UINT8 (tx_interval, p);
    STREAM_TO_UINT8 (retrans_window, p);
    STREAM_TO_UINT16 (rx_pkt_len, p);
    STREAM_TO_UINT16 (tx_pkt_len, p);

    btm_esco_proc_conn_chg (status, handle, tx_interval, retrans_window,
                            rx_pkt_len, tx_pkt_len);
#endif
}