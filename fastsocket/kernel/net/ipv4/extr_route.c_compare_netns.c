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
struct rtable {TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ dev_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int compare_netns(struct rtable *rt1, struct rtable *rt2)
{
	return dev_net(rt1->u.dst.dev) == dev_net(rt2->u.dst.dev);
}