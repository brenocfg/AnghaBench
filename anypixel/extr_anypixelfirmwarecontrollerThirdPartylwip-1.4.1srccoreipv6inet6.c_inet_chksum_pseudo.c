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
typedef  int u8_t ;
typedef  int u32_t ;
typedef  int u16_t ;
struct pbuf {int len; int /*<<< orphan*/  payload; struct pbuf* next; } ;
struct ip_addr {scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ chksum (int /*<<< orphan*/ ,int) ; 
 scalar_t__ htons (int) ; 

u16_t
inet_chksum_pseudo(struct pbuf *p,
       struct ip_addr *src, struct ip_addr *dest,
       u8_t proto, u32_t proto_len)
{
  u32_t acc;
  struct pbuf *q;
  u8_t swapped, i;

  acc = 0;
  swapped = 0;
  for(q = p; q != NULL; q = q->next) {    
    acc += chksum(q->payload, q->len);
    while (acc >> 16) {
      acc = (acc & 0xffff) + (acc >> 16);
    }
    if (q->len % 2 != 0) {
      swapped = 1 - swapped;
      acc = ((acc & 0xff) << 8) | ((acc & 0xff00) >> 8);
    }
  }

  if (swapped) {
    acc = ((acc & 0xff) << 8) | ((acc & 0xff00) >> 8);
  }
  
  for(i = 0; i < 8; i++) {
    acc += ((u16_t *)src->addr)[i] & 0xffff;
    acc += ((u16_t *)dest->addr)[i] & 0xffff;
    while (acc >> 16) {
      acc = (acc & 0xffff) + (acc >> 16);
    }
  }
  acc += (u16_t)htons((u16_t)proto);
  acc += ((u16_t *)&proto_len)[0] & 0xffff;
  acc += ((u16_t *)&proto_len)[1] & 0xffff;

  while (acc >> 16) {
    acc = (acc & 0xffff) + (acc >> 16);
  }
  return ~(acc & 0xffff);
}