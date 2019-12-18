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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int /*<<< orphan*/  u16_t ;

/* Variables and functions */
 int /*<<< orphan*/ * dev_alloc_skb (int /*<<< orphan*/ ) ; 

zbuf_t* zfwBufAllocate(zdev_t* dev, u16_t len)
{
    zbuf_t* buf;

    /* Allocate SKB for packet*/
    buf = dev_alloc_skb(len);

    return buf;
}