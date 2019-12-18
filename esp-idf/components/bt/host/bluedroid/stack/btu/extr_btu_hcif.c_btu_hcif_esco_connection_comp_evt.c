#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  bd_addr; int /*<<< orphan*/  air_mode; int /*<<< orphan*/  tx_pkt_len; int /*<<< orphan*/  rx_pkt_len; int /*<<< orphan*/  retrans_window; int /*<<< orphan*/  tx_interval; int /*<<< orphan*/  link_type; } ;
typedef  TYPE_1__ tBTM_ESCO_DATA ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  STREAM_TO_BDADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btm_sco_connected (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btu_hcif_esco_connection_comp_evt (UINT8 *p)
{
#if BTM_SCO_INCLUDED == TRUE
    tBTM_ESCO_DATA  data;
    UINT16          handle;
    BD_ADDR         bda;
    UINT8           status;

    STREAM_TO_UINT8 (status, p);
    STREAM_TO_UINT16 (handle, p);
    STREAM_TO_BDADDR (bda, p);

    STREAM_TO_UINT8 (data.link_type, p);
    STREAM_TO_UINT8 (data.tx_interval, p);
    STREAM_TO_UINT8 (data.retrans_window, p);
    STREAM_TO_UINT16 (data.rx_pkt_len, p);
    STREAM_TO_UINT16 (data.tx_pkt_len, p);
    STREAM_TO_UINT8 (data.air_mode, p);

    memcpy (data.bd_addr, bda, BD_ADDR_LEN);
    btm_sco_connected (status, bda, handle, &data);
#endif
}