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
struct pasemi_mac_rxring {int dummy; } ;
struct pasemi_mac {struct pasemi_mac_rxring* rx; } ;

/* Variables and functions */

__attribute__((used)) static struct pasemi_mac_rxring *rx_ring(const struct pasemi_mac *mac)
{
	return mac->rx;
}