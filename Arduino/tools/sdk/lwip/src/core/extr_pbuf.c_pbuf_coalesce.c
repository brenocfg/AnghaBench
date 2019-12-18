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
struct pbuf {int /*<<< orphan*/  tot_len; int /*<<< orphan*/ * next; } ;
typedef  int /*<<< orphan*/  pbuf_layer ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  LWIP_ASSERT (char*,int) ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 struct pbuf* pbuf_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pbuf_copy (struct pbuf*,struct pbuf*) ; 
 int /*<<< orphan*/  pbuf_free (struct pbuf*) ; 

struct pbuf*
pbuf_coalesce(struct pbuf *p, pbuf_layer layer)
{
  struct pbuf *q;
  err_t err;
  if (p->next == NULL) {
    return p;
  }
  q = pbuf_alloc(layer, p->tot_len, PBUF_RAM);
  if (q == NULL) {
    /* @todo: what do we do now? */
    return p;
  }
  err = pbuf_copy(q, p);
  LWIP_ASSERT("pbuf_copy failed", err == ERR_OK);
  pbuf_free(p);
  return q;
}