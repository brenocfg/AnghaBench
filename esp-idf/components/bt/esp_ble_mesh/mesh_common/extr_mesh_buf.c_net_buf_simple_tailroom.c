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
struct net_buf_simple {size_t size; size_t len; } ;

/* Variables and functions */
 size_t net_buf_simple_headroom (struct net_buf_simple*) ; 

size_t net_buf_simple_tailroom(struct net_buf_simple *buf)
{
    return buf->size - net_buf_simple_headroom(buf) - buf->len;
}