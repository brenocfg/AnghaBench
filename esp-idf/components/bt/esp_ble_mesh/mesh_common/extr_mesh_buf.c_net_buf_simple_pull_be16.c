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
struct net_buf_simple {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNALIGNED_GET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_buf_simple_pull (struct net_buf_simple*,int) ; 
 int /*<<< orphan*/  sys_be16_to_cpu (int /*<<< orphan*/ ) ; 

u16_t net_buf_simple_pull_be16(struct net_buf_simple *buf)
{
    u16_t val;

    val = UNALIGNED_GET((u16_t *)buf->data);
    net_buf_simple_pull(buf, sizeof(val));

    return sys_be16_to_cpu(val);
}