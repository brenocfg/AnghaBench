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
struct netif {char* name; int mtu; int /*<<< orphan*/  state; scalar_t__ num; int /*<<< orphan*/  flags; int /*<<< orphan*/  output; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_IF ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NETIF_FLAG_POINTTOPOINT ; 
 int /*<<< orphan*/  SLIPIF_THREAD_PRIO ; 
 int /*<<< orphan*/  SLIP_DEBUG ; 
 int /*<<< orphan*/  sio_open (scalar_t__) ; 
 int /*<<< orphan*/  slipif_loop ; 
 int /*<<< orphan*/  slipif_output ; 
 int /*<<< orphan*/  sys_thread_new (int /*<<< orphan*/ ,struct netif*,int /*<<< orphan*/ ) ; 

err_t
slipif_init(struct netif *netif)
{

  LWIP_DEBUGF(SLIP_DEBUG, ("slipif_init: netif->num=%x\n", (int)netif->num));

  netif->name[0] = 's';
  netif->name[1] = 'l';
  netif->output = slipif_output;
  netif->mtu = 1500;
  netif->flags = NETIF_FLAG_POINTTOPOINT;

  netif->state = sio_open(netif->num);
  if (!netif->state)
      return ERR_IF;

  sys_thread_new(slipif_loop, netif, SLIPIF_THREAD_PRIO);
  return ERR_OK;
}