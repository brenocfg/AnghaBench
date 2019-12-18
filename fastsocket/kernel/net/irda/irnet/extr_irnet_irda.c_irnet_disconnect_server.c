#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tsap; int /*<<< orphan*/  rname; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
typedef  TYPE_1__ irnet_socket ;

/* Variables and functions */
 int /*<<< orphan*/  DENTER (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  DEXIT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IRDA_SERV_TRACE ; 
 int /*<<< orphan*/  IRNET_REQUEST_FROM ; 
 int /*<<< orphan*/  P_NORMAL ; 
 int /*<<< orphan*/  irnet_post_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irttp_disconnect_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irttp_listen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

__attribute__((used)) static inline void
irnet_disconnect_server(irnet_socket *	self,
			struct sk_buff *skb)
{
  DENTER(IRDA_SERV_TRACE, "(self=0x%p)\n", self);

  /* Put the received packet in the black hole */
  kfree_skb(skb);

#ifdef FAIL_SEND_DISCONNECT
  /* Tell the other party we don't want to be connected */
  /* Hum... Is it the right thing to do ? And do we need to send
   * a connect response before ? It looks ok without this... */
  irttp_disconnect_request(self->tsap, NULL, P_NORMAL);
#endif /* FAIL_SEND_DISCONNECT */

  /* Notify the control channel (see irnet_find_socket()) */
  irnet_post_event(NULL, IRNET_REQUEST_FROM,
		   self->saddr, self->daddr, self->rname, 0);

  /* Clean up the server to keep it in listen state */
  irttp_listen(self->tsap);

  DEXIT(IRDA_SERV_TRACE, "\n");
  return;
}