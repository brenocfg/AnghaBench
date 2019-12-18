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
typedef  int u8_t ;
struct netif {int flags; } ;

/* Variables and functions */
 int NETIF_FLAG_UP ; 

u8_t netif_is_up(struct netif *netif)
{
  return (netif->flags & NETIF_FLAG_UP)?1:0;
}