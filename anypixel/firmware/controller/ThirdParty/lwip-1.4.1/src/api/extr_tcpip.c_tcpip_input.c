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
struct TYPE_3__ {struct netif* netif; struct pbuf* p; } ;
struct TYPE_4__ {TYPE_1__ inp; } ;
struct tcpip_msg {TYPE_2__ msg; int /*<<< orphan*/  type; } ;
struct pbuf {int dummy; } ;
struct netif {int flags; } ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 scalar_t__ ERR_MEM ; 
 scalar_t__ ERR_OK ; 
 scalar_t__ ERR_VAL ; 
 int /*<<< orphan*/  LOCK_TCPIP_CORE () ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MEMP_TCPIP_MSG_INPKT ; 
 int NETIF_FLAG_ETHARP ; 
 int NETIF_FLAG_ETHERNET ; 
 int /*<<< orphan*/  TCPIP_DEBUG ; 
 int /*<<< orphan*/  TCPIP_MSG_INPKT ; 
 int /*<<< orphan*/  UNLOCK_TCPIP_CORE () ; 
 scalar_t__ ethernet_input (struct pbuf*,struct netif*) ; 
 scalar_t__ ip_input (struct pbuf*,struct netif*) ; 
 int /*<<< orphan*/  mbox ; 
 int /*<<< orphan*/  memp_free (int /*<<< orphan*/ ,struct tcpip_msg*) ; 
 scalar_t__ memp_malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ sys_mbox_trypost (int /*<<< orphan*/ *,struct tcpip_msg*) ; 
 int /*<<< orphan*/  sys_mbox_valid (int /*<<< orphan*/ *) ; 

err_t
tcpip_input(struct pbuf *p, struct netif *inp)
{
#if LWIP_TCPIP_CORE_LOCKING_INPUT
  err_t ret;
  LWIP_DEBUGF(TCPIP_DEBUG, ("tcpip_input: PACKET %p/%p\n", (void *)p, (void *)inp));
  LOCK_TCPIP_CORE();
#if LWIP_ETHERNET
  if (inp->flags & (NETIF_FLAG_ETHARP | NETIF_FLAG_ETHERNET)) {
    ret = ethernet_input(p, inp);
  } else
#endif /* LWIP_ETHERNET */
  {
    ret = ip_input(p, inp);
  }
  UNLOCK_TCPIP_CORE();
  return ret;
#else /* LWIP_TCPIP_CORE_LOCKING_INPUT */
  struct tcpip_msg *msg;

  if (!sys_mbox_valid(&mbox)) {
    return ERR_VAL;
  }
  msg = (struct tcpip_msg *)memp_malloc(MEMP_TCPIP_MSG_INPKT);
  if (msg == NULL) {
    return ERR_MEM;
  }

  msg->type = TCPIP_MSG_INPKT;
  msg->msg.inp.p = p;
  msg->msg.inp.netif = inp;
  if (sys_mbox_trypost(&mbox, msg) != ERR_OK) {
    memp_free(MEMP_TCPIP_MSG_INPKT, msg);
    return ERR_MEM;
  }
  return ERR_OK;
#endif /* LWIP_TCPIP_CORE_LOCKING_INPUT */
}