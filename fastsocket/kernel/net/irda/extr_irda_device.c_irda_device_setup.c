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
struct net_device {int tx_queue_len; int mtu; int /*<<< orphan*/  flags; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  type; int /*<<< orphan*/  addr_len; scalar_t__ hard_header_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_IRDA ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  LAP_ALEN ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void irda_device_setup(struct net_device *dev)
{
	dev->hard_header_len = 0;
	dev->addr_len        = LAP_ALEN;

	dev->type            = ARPHRD_IRDA;
	dev->tx_queue_len    = 8; /* Window size + 1 s-frame */

	memset(dev->broadcast, 0xff, LAP_ALEN);

	dev->mtu = 2048;
	dev->flags = IFF_NOARP;
}