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
typedef  scalar_t__ u8_t ;
struct pbuf {scalar_t__ tot_len; scalar_t__ len; struct pbuf* next; } ;

/* Variables and functions */
 int DBG_STATE ; 
 int /*<<< orphan*/  LWIP_ASSERT (char*,int) ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int,char*) ; 
 int PBUF_DEBUG ; 
 scalar_t__ pbuf_free (struct pbuf*) ; 

struct pbuf *
pbuf_dechain(struct pbuf *p)
{
  struct pbuf *q;
  u8_t tail_gone = 1;
  /* tail */
  q = p->next;
  /* pbuf has successor in chain? */
  if (q != NULL) {
    /* assert tot_len invariant: (p->tot_len == p->len + (p->next? p->next->tot_len: 0) */
    LWIP_ASSERT("p->tot_len == p->len + q->tot_len", q->tot_len == p->tot_len - p->len);
    /* enforce invariant if assertion is disabled */
    q->tot_len = p->tot_len - p->len;
    /* decouple pbuf from remainder */
    p->next = NULL;
    /* total length of pbuf p is its own length only */
    p->tot_len = p->len;
    /* q is no longer referenced by p, free it */
    LWIP_DEBUGF(PBUF_DEBUG | DBG_STATE, ("pbuf_dechain: unreferencing %p\n", (void *)q));
    tail_gone = pbuf_free(q);
    if (tail_gone > 0) {
      LWIP_DEBUGF(PBUF_DEBUG | DBG_STATE,
                  ("pbuf_dechain: deallocated %p (as it is no longer referenced)\n", (void *)q));
    }
    /* return remaining tail or NULL if deallocated */
  }
  /* assert tot_len invariant: (p->tot_len == p->len + (p->next? p->next->tot_len: 0) */
  LWIP_ASSERT("p->tot_len == p->len", p->tot_len == p->len);
  return (tail_gone > 0? NULL: q);
}