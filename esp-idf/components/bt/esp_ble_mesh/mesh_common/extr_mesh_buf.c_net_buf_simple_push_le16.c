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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  u16_t ;
struct net_buf_simple {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NET_BUF_SIMPLE_DBG (char*,struct net_buf_simple*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  net_buf_simple_push (struct net_buf_simple*,int) ; 
 int /*<<< orphan*/  sys_cpu_to_le16 (int /*<<< orphan*/ ) ; 

void net_buf_simple_push_le16(struct net_buf_simple *buf, u16_t val)
{
    NET_BUF_SIMPLE_DBG("buf %p val %u", buf, val);

    val = sys_cpu_to_le16(val);
    memcpy(net_buf_simple_push(buf, sizeof(val)), &val, sizeof(val));
}