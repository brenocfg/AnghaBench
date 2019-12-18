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

/* Variables and functions */
 int DBG_FRESH ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int,char*) ; 
 int PBUF_DEBUG ; 
 int /*<<< orphan*/  pbuf_cat (struct pbuf*,struct pbuf*) ; 
 int /*<<< orphan*/  pbuf_ref (struct pbuf*) ; 

void
pbuf_chain(struct pbuf *h, struct pbuf *t)
{
  pbuf_cat(h, t);
  /* t is now referenced by h */
  pbuf_ref(t);
  LWIP_DEBUGF(PBUF_DEBUG | DBG_FRESH | 2, ("pbuf_chain: %p references %p\n", (void *)h, (void *)t));
}