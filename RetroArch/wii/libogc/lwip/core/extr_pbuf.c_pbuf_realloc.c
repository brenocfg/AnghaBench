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
typedef  int /*<<< orphan*/  u8_t ;
typedef  scalar_t__ u16_t ;
struct pbuf {scalar_t__ flags; scalar_t__ tot_len; scalar_t__ len; struct pbuf* next; scalar_t__ payload; } ;
typedef  scalar_t__ s16_t ;

/* Variables and functions */
 int /*<<< orphan*/  LWIP_ASSERT (char*,int) ; 
 scalar_t__ PBUF_FLAG_POOL ; 
 scalar_t__ PBUF_FLAG_RAM ; 
 scalar_t__ PBUF_FLAG_REF ; 
 scalar_t__ PBUF_FLAG_ROM ; 
 int /*<<< orphan*/  mem_realloc (struct pbuf*,scalar_t__) ; 
 int /*<<< orphan*/  pbuf_free (struct pbuf*) ; 

void
pbuf_realloc(struct pbuf *p, u16_t new_len)
{
  struct pbuf *q;
  u16_t rem_len; /* remaining length */
  s16_t grow;

  LWIP_ASSERT("pbuf_realloc: sane p->flags", p->flags == PBUF_FLAG_POOL ||
              p->flags == PBUF_FLAG_ROM ||
              p->flags == PBUF_FLAG_RAM ||
              p->flags == PBUF_FLAG_REF);

  /* desired length larger than current length? */
  if (new_len >= p->tot_len) {
    /* enlarging not yet supported */
    return;
  }

  /* the pbuf chain grows by (new_len - p->tot_len) bytes
   * (which may be negative in case of shrinking) */
  grow = new_len - p->tot_len;

  /* first, step over any pbufs that should remain in the chain */
  rem_len = new_len;
  q = p;
  /* should this pbuf be kept? */
  while (rem_len > q->len) {
    /* decrease remaining length by pbuf length */
    rem_len -= q->len;
    /* decrease total length indicator */
    q->tot_len += grow;
    /* proceed to next pbuf in chain */
    q = q->next;
  }
  /* we have now reached the new last pbuf (in q) */
  /* rem_len == desired length for pbuf q */

  /* shrink allocated memory for PBUF_RAM */
  /* (other types merely adjust their length fields */
  if ((q->flags == PBUF_FLAG_RAM) && (rem_len != q->len)) {
    /* reallocate and adjust the length of the pbuf that will be split */
    mem_realloc(q, (u8_t *)q->payload - (u8_t *)q + rem_len);
  }
  /* adjust length fields for new last pbuf */
  q->len = rem_len;
  q->tot_len = q->len;

  /* any remaining pbufs in chain? */
  if (q->next != NULL) {
    /* free remaining pbufs in chain */
    pbuf_free(q->next);
  }
  /* q is last packet in chain */
  q->next = NULL;

}