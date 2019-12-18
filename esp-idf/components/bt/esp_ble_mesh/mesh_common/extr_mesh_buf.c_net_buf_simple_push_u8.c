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
struct net_buf_simple {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * net_buf_simple_push (struct net_buf_simple*,int) ; 

void net_buf_simple_push_u8(struct net_buf_simple *buf, u8_t val)
{
    u8_t *data = net_buf_simple_push(buf, 1);

    *data = val;
}