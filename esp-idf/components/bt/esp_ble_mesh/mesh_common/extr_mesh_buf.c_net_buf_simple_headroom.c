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
struct net_buf_simple {size_t data; size_t __buf; } ;

/* Variables and functions */

size_t net_buf_simple_headroom(struct net_buf_simple *buf)
{
    return buf->data - buf->__buf;
}