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
typedef  int u32_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct uip_pbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  payload; struct uip_pbuf* next; } ;

/* Variables and functions */
 scalar_t__ uip_chksum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u16_t uip_ipchksum_pbuf(struct uip_pbuf *p)
{
  u32_t acc;
  struct uip_pbuf *q;

  acc = 0;
  for(q = p; q != NULL; q = q->next) {
	acc += uip_chksum(q->payload,q->len);
  }
  while(acc>>16) acc = (acc&0xffffUL)+(acc>>16);

  return (u16_t)~(acc & 0xffffUL);
}