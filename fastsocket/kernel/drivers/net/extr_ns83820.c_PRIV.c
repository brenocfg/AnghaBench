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
struct ns83820 {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct ns83820* netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline struct ns83820 *PRIV(struct net_device *dev)
{
	return netdev_priv(dev);
}