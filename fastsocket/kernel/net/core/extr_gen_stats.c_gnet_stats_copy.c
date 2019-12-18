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
struct gnet_dump {int /*<<< orphan*/  lock; int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLA_PUT (int /*<<< orphan*/ ,int,int,void*) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
gnet_stats_copy(struct gnet_dump *d, int type, void *buf, int size)
{
	NLA_PUT(d->skb, type, size, buf);
	return 0;

nla_put_failure:
	spin_unlock_bh(d->lock);
	return -1;
}