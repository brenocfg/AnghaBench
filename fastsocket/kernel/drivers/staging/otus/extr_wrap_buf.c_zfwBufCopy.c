#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; int /*<<< orphan*/  tail; } ;
typedef  TYPE_1__ zbuf_t ;
typedef  int /*<<< orphan*/  u16_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (TYPE_1__*,int /*<<< orphan*/ ) ; 

u16_t zfwBufCopy(zdev_t* dev, zbuf_t* dst, zbuf_t* src)
{
    memcpy(dst->data, src->data, src->len);
    dst->tail = dst->data;
    skb_put(dst, src->len);
    return 0;
}