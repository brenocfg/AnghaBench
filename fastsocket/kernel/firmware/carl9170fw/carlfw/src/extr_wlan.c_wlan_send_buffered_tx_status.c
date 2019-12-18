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
struct TYPE_3__ {size_t tx_status_head_idx; scalar_t__ tx_status_pending; int /*<<< orphan*/ * tx_status_cache; } ;
struct TYPE_4__ {TYPE_1__ wlan; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170_RSP_TXCOMP ; 
 size_t CARL9170_RSP_TX_STATUS_NUM ; 
 size_t CARL9170_TX_STATUS_NUM ; 
 TYPE_2__ fw ; 
 unsigned int min (unsigned int,size_t) ; 
 int /*<<< orphan*/  send_cmd_to_host (unsigned int,int /*<<< orphan*/ ,unsigned int,void*) ; 

__attribute__((used)) static void wlan_send_buffered_tx_status(void)
{
	unsigned int len;

	while (fw.wlan.tx_status_pending) {
		len = min((unsigned int)fw.wlan.tx_status_pending,
			  CARL9170_RSP_TX_STATUS_NUM);
		len = min(len, CARL9170_TX_STATUS_NUM -	fw.wlan.tx_status_head_idx);

		/*
		 * rather than memcpy each individual request into a large buffer,
		 * we _splice_ them all together.
		 *
		 * The only downside is however that we have to be careful around
		 * the edges of the tx_status_cache.
		 *
		 * Note:
		 * Each tx_status is about 2 bytes. However every command package
		 * must have a size which is a multiple of 4.
		 */

		send_cmd_to_host((len * sizeof(struct carl9170_tx_status) + 3) & ~3,
				 CARL9170_RSP_TXCOMP, len, (void *)
				 &fw.wlan.tx_status_cache[fw.wlan.tx_status_head_idx]);

		fw.wlan.tx_status_pending -= len;
		fw.wlan.tx_status_head_idx += len;
		fw.wlan.tx_status_head_idx %= CARL9170_TX_STATUS_NUM;
	}
}