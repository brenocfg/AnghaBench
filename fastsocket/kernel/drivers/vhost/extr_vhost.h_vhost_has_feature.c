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
struct vhost_dev {int /*<<< orphan*/  acked_features; } ;

/* Variables and functions */
 unsigned int rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int vhost_has_feature(struct vhost_dev *dev, int bit)
{
	unsigned acked_features = rcu_dereference(dev->acked_features);
	return acked_features & (1 << bit);
}