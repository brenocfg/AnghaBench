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
 int /*<<< orphan*/  NET_BUF_SIMPLE_DBG (char*,struct net_buf_simple*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * net_buf_simple_add (struct net_buf_simple*,int) ; 

u8_t *net_buf_simple_add_u8(struct net_buf_simple *buf, u8_t val)
{
    u8_t *u8;

    NET_BUF_SIMPLE_DBG("buf %p val 0x%02x", buf, val);

    u8 = net_buf_simple_add(buf, 1);
    *u8 = val;

    return u8;
}