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
typedef  scalar_t__ uint32_t ;
struct net_device {int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETIF_F_TSO ; 
 int /*<<< orphan*/  NETIF_F_TSO6 ; 

__attribute__((used)) static int ql_set_tso(struct net_device *ndev, uint32_t data)
{

	if (data) {
		ndev->features |= NETIF_F_TSO;
		ndev->features |= NETIF_F_TSO6;
	} else {
		ndev->features &= ~NETIF_F_TSO;
		ndev->features &= ~NETIF_F_TSO6;
	}
	return 0;
}