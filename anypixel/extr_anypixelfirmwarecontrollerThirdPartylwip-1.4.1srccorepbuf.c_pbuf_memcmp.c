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
typedef  scalar_t__ u16_t ;
struct pbuf {scalar_t__ len; struct pbuf* next; } ;

/* Variables and functions */
 scalar_t__ pbuf_get_at (struct pbuf*,scalar_t__) ; 

u16_t
pbuf_memcmp(struct pbuf* p, u16_t offset, const void* s2, u16_t n)
{
  u16_t start = offset;
  struct pbuf* q = p;

  /* get the correct pbuf */
  while ((q != NULL) && (q->len <= start)) {
    start -= q->len;
    q = q->next;
  }
  /* return requested data if pbuf is OK */
  if ((q != NULL) && (q->len > start)) {
    u16_t i;
    for(i = 0; i < n; i++) {
      u8_t a = pbuf_get_at(q, start + i);
      u8_t b = ((u8_t*)s2)[i];
      if (a != b) {
        return i+1;
      }
    }
    return 0;
  }
  return 0xffff;
}