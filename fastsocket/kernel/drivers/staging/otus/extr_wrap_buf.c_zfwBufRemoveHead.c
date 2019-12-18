#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ zbuf_t ;
typedef  scalar_t__ u16_t ;

/* Variables and functions */

u16_t zfwBufRemoveHead(zdev_t* dev, zbuf_t* buf, u16_t size)
{
    //zm_assert(buf->len > size);

    buf->data += size;
    buf->len -= size;
    return 0;
}