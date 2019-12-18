#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_2__ {int /*<<< orphan*/  handle_char_e2p; int /*<<< orphan*/  conn_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GATTS_HandleValueIndication (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 TYPE_1__ blufi_env ; 

__attribute__((used)) static void btc_blufi_send_notify(uint8_t *pkt, int pkt_len)
{
    UINT16 conn_id = blufi_env.conn_id;
    UINT16 attr_id = blufi_env.handle_char_e2p;
    bool rsp = false;

    BTA_GATTS_HandleValueIndication(conn_id, attr_id, pkt_len,
                                     pkt, rsp);
}