#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* MacInfo; } ;
struct sliccard {TYPE_2__ config; scalar_t__ config_set; } ;
struct slic_config_mac {int dummy; } ;
struct adapter {size_t functionnumber; scalar_t__* currmacaddr; TYPE_3__* netdev; scalar_t__* macaddr; struct sliccard* card; } ;
struct TYPE_6__ {scalar_t__* dev_addr; } ;
struct TYPE_4__ {scalar_t__* macaddrA; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static void slic_adapter_set_hwaddr(struct adapter *adapter)
{
	struct sliccard *card = adapter->card;

	if ((adapter->card) && (card->config_set)) {
		memcpy(adapter->macaddr,
		       card->config.MacInfo[adapter->functionnumber].macaddrA,
		       sizeof(struct slic_config_mac));
		if (!(adapter->currmacaddr[0] || adapter->currmacaddr[1] ||
		      adapter->currmacaddr[2] || adapter->currmacaddr[3] ||
		      adapter->currmacaddr[4] || adapter->currmacaddr[5])) {
			memcpy(adapter->currmacaddr, adapter->macaddr, 6);
		}
		if (adapter->netdev) {
			memcpy(adapter->netdev->dev_addr, adapter->currmacaddr,
			       6);
		}
	}
}