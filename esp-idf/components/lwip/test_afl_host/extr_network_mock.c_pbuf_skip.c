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
typedef  scalar_t__ u16_t ;
struct pbuf {scalar_t__ len; struct pbuf* next; } ;

/* Variables and functions */

struct pbuf* pbuf_skip(struct pbuf* in, u16_t in_offset, u16_t* out_offset)
{
    u16_t offset_left = in_offset;
    struct pbuf* q = in;

    /* get the correct pbuf */
    while ((q != NULL) && (q->len <= offset_left)) {
        offset_left -= q->len;
        q = q->next;
    }
    if (out_offset != NULL) {
        *out_offset = offset_left;
    }
    return q;
}