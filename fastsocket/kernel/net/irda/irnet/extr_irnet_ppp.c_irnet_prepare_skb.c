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
struct sk_buff {unsigned char* data; } ;
struct TYPE_4__ {int flags; scalar_t__ max_header_size; } ;
typedef  TYPE_1__ irnet_socket ;

/* Variables and functions */
 int /*<<< orphan*/  DABORT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DENTER (int /*<<< orphan*/ ,char*,TYPE_1__*,struct sk_buff*) ; 
 int /*<<< orphan*/  DEXIT (int /*<<< orphan*/ ,char*) ; 
 unsigned char PPP_ALLSTATIONS ; 
 int /*<<< orphan*/  PPP_ERROR ; 
 int /*<<< orphan*/  PPP_INFO ; 
 int PPP_LCP ; 
 int /*<<< orphan*/  PPP_TRACE ; 
 unsigned char PPP_UI ; 
 int SC_COMP_AC ; 
 int SC_COMP_PROT ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 struct sk_buff* skb_realloc_headroom (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_shared (struct sk_buff*) ; 

__attribute__((used)) static inline struct sk_buff *
irnet_prepare_skb(irnet_socket *	ap,
		  struct sk_buff *	skb)
{
  unsigned char *	data;
  int			proto;		/* PPP protocol */
  int			islcp;		/* Protocol == LCP */
  int			needaddr;	/* Need PPP address */

  DENTER(PPP_TRACE, "(ap=0x%p, skb=0x%p)\n",
	 ap, skb);

  /* Extract PPP protocol from the frame */
  data  = skb->data;
  proto = (data[0] << 8) + data[1];

  /* LCP packets with codes between 1 (configure-request)
   * and 7 (code-reject) must be sent as though no options
   * have been negotiated. */
  islcp = (proto == PPP_LCP) && (1 <= data[2]) && (data[2] <= 7);

  /* compress protocol field if option enabled */
  if((data[0] == 0) && (ap->flags & SC_COMP_PROT) && (!islcp))
    skb_pull(skb,1);

  /* Check if we need address/control fields */
  needaddr = 2*((ap->flags & SC_COMP_AC) == 0 || islcp);

  /* Is the skb headroom large enough to contain all IrDA-headers? */
  if((skb_headroom(skb) < (ap->max_header_size + needaddr)) ||
      (skb_shared(skb)))
    {
      struct sk_buff *	new_skb;

      DEBUG(PPP_INFO, "Reallocating skb\n");

      /* Create a new skb */
      new_skb = skb_realloc_headroom(skb, ap->max_header_size + needaddr);

      /* We have to free the original skb anyway */
      dev_kfree_skb(skb);

      /* Did the realloc succeed ? */
      DABORT(new_skb == NULL, NULL, PPP_ERROR, "Could not realloc skb\n");

      /* Use the new skb instead */
      skb = new_skb;
    }

  /* prepend address/control fields if necessary */
  if(needaddr)
    {
      skb_push(skb, 2);
      skb->data[0] = PPP_ALLSTATIONS;
      skb->data[1] = PPP_UI;
    }

  DEXIT(PPP_TRACE, "\n");

  return skb;
}