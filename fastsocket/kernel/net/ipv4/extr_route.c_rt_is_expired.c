#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ dst; } ;
struct rtable {scalar_t__ rt_genid; TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 scalar_t__ rt_genid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int rt_is_expired(struct rtable *rth)
{
	return rth->rt_genid != rt_genid(dev_net(rth->u.dst.dev));
}