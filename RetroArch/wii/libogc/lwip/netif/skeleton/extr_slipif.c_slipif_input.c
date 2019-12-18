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
typedef  int u8_t ;
struct pbuf {int len; scalar_t__ payload; } ;
struct netif {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  drop; int /*<<< orphan*/  recv; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_STATS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  PBUF_LINK ; 
 int /*<<< orphan*/  PBUF_POOL ; 
 int /*<<< orphan*/  PBUF_POOL_BUFSIZE ; 
 int /*<<< orphan*/  SLIP_DEBUG ; 
#define  SLIP_END 131 
#define  SLIP_ESC 130 
#define  SLIP_ESC_END 129 
#define  SLIP_ESC_ESC 128 
 TYPE_1__ link ; 
 struct pbuf* pbuf_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pbuf_cat (struct pbuf*,struct pbuf*) ; 
 int /*<<< orphan*/  pbuf_realloc (struct pbuf*,int) ; 
 int sio_recv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pbuf *
slipif_input( struct netif * netif )
{
  u8_t c;
  struct pbuf *p, *q;
  int recved;
  int i;

  q = p = NULL;
  recved = i = 0;
  c = 0;

  while (1) {
    c = sio_recv(netif->state);
    switch (c) {
    case SLIP_END:
      if (recved > 0) {
  /* Received whole packet. */
  pbuf_realloc(q, recved);

  LINK_STATS_INC(link.recv);

  LWIP_DEBUGF(SLIP_DEBUG, ("slipif: Got packet\n"));
  return q;
      }
      break;

    case SLIP_ESC:
      c = sio_recv(netif->state);
      switch (c) {
      case SLIP_ESC_END:
  c = SLIP_END;
  break;
      case SLIP_ESC_ESC:
  c = SLIP_ESC;
  break;
      }
      /* FALLTHROUGH */

    default:
      if (p == NULL) {
  LWIP_DEBUGF(SLIP_DEBUG, ("slipif_input: alloc\n"));
  p = pbuf_alloc(PBUF_LINK, PBUF_POOL_BUFSIZE, PBUF_POOL);

  if (p == NULL) {
    LINK_STATS_INC(link.drop);
    LWIP_DEBUGF(SLIP_DEBUG, ("slipif_input: no new pbuf! (DROP)\n"));
  }

  if (q != NULL) {
    pbuf_cat(q, p);
  } else {
    q = p;
  }
      }
      if (p != NULL && recved < MAX_SIZE) {
  ((u8_t *)p->payload)[i] = c;
  recved++;
  i++;
  if (i >= p->len) {
    i = 0;
    p = NULL;
  }
      }
      break;
    }

  }
  return NULL;
}