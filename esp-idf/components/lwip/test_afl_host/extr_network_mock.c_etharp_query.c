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
struct pbuf {int dummy; } ;
struct netif {int dummy; } ;
typedef  int /*<<< orphan*/  ip4_addr_t ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 

err_t etharp_query(struct netif *netif, const ip4_addr_t *ipaddr, struct pbuf *q)
{
    return ESP_OK;
}