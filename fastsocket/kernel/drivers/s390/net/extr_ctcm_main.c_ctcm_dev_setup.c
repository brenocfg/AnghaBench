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
struct net_device {int tx_queue_len; int flags; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_SLIP ; 
 int IFF_NOARP ; 
 int IFF_POINTOPOINT ; 

__attribute__((used)) void static ctcm_dev_setup(struct net_device *dev)
{
	dev->type = ARPHRD_SLIP;
	dev->tx_queue_len = 100;
	dev->flags = IFF_POINTOPOINT | IFF_NOARP;
}