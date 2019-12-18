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
struct net_device {int dummy; } ;
struct dscc4_dev_priv {struct net_device* dev; } ;

/* Variables and functions */

__attribute__((used)) static inline struct net_device *dscc4_to_dev(struct dscc4_dev_priv *p)
{
	return p->dev;
}