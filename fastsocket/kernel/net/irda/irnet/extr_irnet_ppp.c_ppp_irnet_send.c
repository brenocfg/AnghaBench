#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct ppp_channel {scalar_t__ private; } ;
struct irnet_socket {scalar_t__ tx_flow; TYPE_1__* tsap; int /*<<< orphan*/  ttp_connect; int /*<<< orphan*/  ttp_open; } ;
typedef  struct irnet_socket irnet_socket ;
struct TYPE_2__ {int /*<<< orphan*/  tx_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DABORT (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DENTER (int /*<<< orphan*/ ,char*,struct ppp_channel*,struct irnet_socket*) ; 
 int /*<<< orphan*/  DERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  DEXIT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DRETURN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FLOW_START ; 
 int /*<<< orphan*/  PPP_ERROR ; 
 int /*<<< orphan*/  PPP_INFO ; 
 int /*<<< orphan*/  PPP_TRACE ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  irda_irnet_connect (struct irnet_socket*) ; 
 struct sk_buff* irnet_prepare_skb (struct irnet_socket*,struct sk_buff*) ; 
 int irttp_data_request (TYPE_1__*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_len (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ppp_irnet_send(struct ppp_channel *	chan,
	       struct sk_buff *		skb)
{
  irnet_socket *	self = (struct irnet_socket *) chan->private;
  int			ret;

  DENTER(PPP_TRACE, "(channel=0x%p, ap/self=0x%p)\n",
	 chan, self);

  /* Check if things are somewhat valid... */
  DASSERT(self != NULL, 0, PPP_ERROR, "Self is NULL !!!\n");

  /* Check if we are connected */
  if(!(test_bit(0, &self->ttp_open)))
    {
#ifdef CONNECT_IN_SEND
      /* Let's try to connect one more time... */
      /* Note : we won't be connected after this call, but we should be
       * ready for next packet... */
      /* If we are already connecting, this will fail */
      irda_irnet_connect(self);
#endif /* CONNECT_IN_SEND */

      DEBUG(PPP_INFO, "IrTTP not ready ! (%ld-%ld)\n",
	    self->ttp_open, self->ttp_connect);

      /* Note : we can either drop the packet or block the packet.
       *
       * Blocking the packet allow us a better connection time,
       * because by calling ppp_output_wakeup() we can have
       * ppp_generic resending the LCP request immediately to us,
       * rather than waiting for one of pppd periodic transmission of
       * LCP request.
       *
       * On the other hand, if we block all packet, all those periodic
       * transmissions of pppd accumulate in ppp_generic, creating a
       * backlog of LCP request. When we eventually connect later on,
       * we have to transmit all this backlog before we can connect
       * proper (if we don't timeout before).
       *
       * The current strategy is as follow :
       * While we are attempting to connect, we block packets to get
       * a better connection time.
       * If we fail to connect, we drain the queue and start dropping packets
       */
#ifdef BLOCK_WHEN_CONNECT
      /* If we are attempting to connect */
      if(test_bit(0, &self->ttp_connect))
	{
	  /* Blocking packet, ppp_generic will retry later */
	  return 0;
	}
#endif /* BLOCK_WHEN_CONNECT */

      /* Dropping packet, pppd will retry later */
      dev_kfree_skb(skb);
      return 1;
    }

  /* Check if the queue can accept any packet, otherwise block */
  if(self->tx_flow != FLOW_START)
    DRETURN(0, PPP_INFO, "IrTTP queue full (%d skbs)...\n",
	    skb_queue_len(&self->tsap->tx_queue));

  /* Prepare ppp frame for transmission */
  skb = irnet_prepare_skb(self, skb);
  DABORT(skb == NULL, 1, PPP_ERROR, "Prepare skb for Tx failed.\n");

  /* Send the packet to IrTTP */
  ret = irttp_data_request(self->tsap, skb);
  if(ret < 0)
    {
      /*
       * > IrTTPs tx queue is full, so we just have to
       * > drop the frame! You might think that we should
       * > just return -1 and don't deallocate the frame,
       * > but that is dangerous since it's possible that
       * > we have replaced the original skb with a new
       * > one with larger headroom, and that would really
       * > confuse do_dev_queue_xmit() in dev.c! I have
       * > tried :-) DB
       * Correction : we verify the flow control above (self->tx_flow),
       * so we come here only if IrTTP doesn't like the packet (empty,
       * too large, IrTTP not connected). In those rare cases, it's ok
       * to drop it, we don't want to see it here again...
       * Jean II
       */
      DERROR(PPP_ERROR, "IrTTP doesn't like this packet !!! (0x%X)\n", ret);
      /* irttp_data_request already free the packet */
    }

  DEXIT(PPP_TRACE, "\n");
  return 1;	/* Packet has been consumed */
}