#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
struct TYPE_4__ {scalar_t__ len; scalar_t__ data; scalar_t__ tail; } ;
typedef  TYPE_1__ zbuf_t ;
typedef  int /*<<< orphan*/  u16_t ;

/* Variables and functions */
 int /*<<< orphan*/  skb_put (TYPE_1__*,int /*<<< orphan*/ ) ; 

u16_t zfwBufSetSize(zdev_t* dev, zbuf_t* buf, u16_t size)
{
#ifdef NET_SKBUFF_DATA_USES_OFFSET
    buf->tail = 0;
    buf->len = 0;
#else
    buf->tail = buf->data;
    buf->len = 0;
#endif

    skb_put(buf, size);
    return 0;
}