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
struct net_buf_simple {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  net_buf_simple_pull (struct net_buf_simple*,int) ; 

u8_t net_buf_simple_pull_u8(struct net_buf_simple *buf)
{
    u8_t val;

    val = buf->data[0];
    net_buf_simple_pull(buf, 1);

    return val;
}