#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct carl9170_tx_status {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_status_pending; int /*<<< orphan*/  tx_status_tail_idx; struct carl9170_tx_status* tx_status_cache; } ;
struct TYPE_4__ {TYPE_1__ wlan; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170_TX_STATUS_NUM ; 
 TYPE_2__ fw ; 
 int /*<<< orphan*/  wlan_send_buffered_tx_status () ; 

__attribute__((used)) static struct carl9170_tx_status *wlan_get_tx_status_buffer(void)
{
	struct carl9170_tx_status *tmp;

	tmp = &fw.wlan.tx_status_cache[fw.wlan.tx_status_tail_idx++];
	fw.wlan.tx_status_tail_idx %= CARL9170_TX_STATUS_NUM;

	if (fw.wlan.tx_status_pending == CARL9170_TX_STATUS_NUM)
		wlan_send_buffered_tx_status();

	fw.wlan.tx_status_pending++;

	return tmp;
}