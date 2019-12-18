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
struct net_device {scalar_t__ name; } ;
struct meta_obj {unsigned long value; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (scalar_t__) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int var_dev(struct net_device *dev, struct meta_obj *dst)
{
	if (unlikely(dev == NULL))
		return -1;

	dst->value = (unsigned long) dev->name;
	dst->len = strlen(dev->name);
	return 0;
}