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
typedef  int u32_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct pbuf {int len; int /*<<< orphan*/  payload; struct pbuf* next; } ;

/* Variables and functions */
 int FOLD_U32T (int) ; 
 scalar_t__ LWIP_CHKSUM (int /*<<< orphan*/ ,int) ; 
 int SWAP_BYTES_IN_WORD (int) ; 

u16_t
inet_chksum_pbuf(struct pbuf *p)
{
  u32_t acc;
  struct pbuf *q;
  u8_t swapped;

  acc = 0;
  swapped = 0;
  for(q = p; q != NULL; q = q->next) {
    acc += LWIP_CHKSUM(q->payload, q->len);
    acc = FOLD_U32T(acc);
    if (q->len % 2 != 0) {
      swapped = 1 - swapped;
      acc = SWAP_BYTES_IN_WORD(acc);
    }
  }

  if (swapped) {
    acc = SWAP_BYTES_IN_WORD(acc);
  }
  return (u16_t)~(acc & 0xffffUL);
}