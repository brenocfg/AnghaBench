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
typedef  size_t u16_t ;
struct pbuf {size_t len; scalar_t__ payload; struct pbuf* next; } ;

/* Variables and functions */

u8_t
pbuf_get_at(struct pbuf* p, u16_t offset)
{
  u16_t copy_from = offset;
  struct pbuf* q = p;

  /* get the correct pbuf */
  while ((q != NULL) && (q->len <= copy_from)) {
    copy_from -= q->len;
    q = q->next;
  }
  /* return requested data if pbuf is OK */
  if ((q != NULL) && (q->len > copy_from)) {
    return ((u8_t*)q->payload)[copy_from];
  }
  return 0;
}