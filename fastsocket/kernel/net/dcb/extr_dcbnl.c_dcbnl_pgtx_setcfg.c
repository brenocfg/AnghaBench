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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int __dcbnl_pg_setcfg (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dcbnl_pgtx_setcfg(struct net_device *netdev, struct nlattr **tb,
                             u32 pid, u32 seq, u16 flags)
{
	return __dcbnl_pg_setcfg(netdev, tb, pid, seq, flags, 0);
}