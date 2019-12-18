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
struct pbuf {size_t len; scalar_t__ payload; } ;

/* Variables and functions */
 struct pbuf* pbuf_skip (struct pbuf*,size_t,size_t*) ; 

void pbuf_put_at(struct pbuf* p, u16_t offset, u8_t data)
{
    u16_t q_idx;
    struct pbuf* q = pbuf_skip(p, offset, &q_idx);

    /* write requested data if pbuf is OK */
    if ((q != NULL) && (q->len > q_idx)) {
        ((u8_t*)q->payload)[q_idx] = data;
    }
}