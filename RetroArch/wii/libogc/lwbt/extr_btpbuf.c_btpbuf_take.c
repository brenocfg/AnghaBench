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
struct pbuf {scalar_t__ flags; scalar_t__ len; struct pbuf* next; int /*<<< orphan*/  tot_len; int /*<<< orphan*/  payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (char*,...) ; 
 scalar_t__ PBUF_FLAG_REF ; 
 int /*<<< orphan*/  PBUF_POOL ; 
 scalar_t__ PBUF_POOL_BUFSIZE ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_RAW ; 
 struct pbuf* btpbuf_alloc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btpbuf_free (struct pbuf*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

struct pbuf* btpbuf_take(struct pbuf *p)
{
	struct pbuf *q , *prev, *head;

	prev = NULL;
	head = p;
	/* iterate through pbuf chain */
	do
	{
		/* pbuf is of type PBUF_REF? */
		if (p->flags == PBUF_FLAG_REF) {
			LOG("pbuf_take: encountered PBUF_REF %p\n", (void *)p);
			/* allocate a pbuf (w/ payload) fully in RAM */
			/* PBUF_POOL buffers are faster if we can use them */
			if (p->len <= PBUF_POOL_BUFSIZE) {
				q = btpbuf_alloc(PBUF_RAW, p->len, PBUF_POOL);
				if (q == NULL) {
					LOG("pbuf_take: Could not allocate PBUF_POOL\n");
				}
			} else {
				/* no replacement pbuf yet */
				q = NULL;
				LOG("pbuf_take: PBUF_POOL too small to replace PBUF_REF\n");
			}
			/* no (large enough) PBUF_POOL was available? retry with PBUF_RAM */
			if (q == NULL) {
				q = btpbuf_alloc(PBUF_RAW, p->len, PBUF_RAM);
				if (q == NULL) {
					LOG("pbuf_take: Could not allocate PBUF_RAM\n");
				}
			}
			/* replacement pbuf could be allocated? */
			if (q != NULL)
			{
				/* copy p to q */
				/* copy successor */
				q->next = p->next;
				/* remove linkage from original pbuf */
				p->next = NULL;
				/* remove linkage to original pbuf */
				if (prev != NULL) {
					/* break chain and insert new pbuf instead */
					prev->next = q;
					/* prev == NULL, so we replaced the head pbuf of the chain */
				} else {
					head = q;
				}
				/* copy pbuf payload */
				memcpy(q->payload, p->payload, p->len);
				q->tot_len = p->tot_len;
				q->len = p->len;
				/* in case p was the first pbuf, it is no longer refered to by
				 * our caller, as the caller MUST do p = pbuf_take(p);
				 * in case p was not the first pbuf, it is no longer refered to
				 * by prev. we can safely free the pbuf here.
				 * (note that we have set p->next to NULL already so that
				 * we will not free the rest of the chain by accident.)
				 */
				btpbuf_free(p);
				/* do not copy ref, since someone else might be using the old buffer */
				LOG("pbuf_take: replaced PBUF_REF %p with %p\n", (void *)p, (void *)q);
				p = q;
			} else {
				/* deallocate chain */
				btpbuf_free(head);
				LOG("pbuf_take: failed to allocate replacement pbuf for %p\n", (void *)p);
				return NULL;
			}
		/* p->flags != PBUF_FLAG_REF */
		} else {
			LOG("pbuf_take: skipping pbuf not of type PBUF_REF\n");
		}
		/* remember this pbuf */
		prev = p;
		/* proceed to next pbuf in original chain */
		p = p->next;
	} while (p);
	LOG("pbuf_take: end of chain reached.\n");

	return head;
}