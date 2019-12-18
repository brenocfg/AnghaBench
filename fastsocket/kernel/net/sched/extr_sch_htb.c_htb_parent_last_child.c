#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct htb_class {TYPE_1__* parent; } ;
struct TYPE_2__ {int children; } ;

/* Variables and functions */

__attribute__((used)) static inline int htb_parent_last_child(struct htb_class *cl)
{
	if (!cl->parent)
		/* the root class */
		return 0;
	if (cl->parent->children > 1)
		/* not the last child */
		return 0;
	return 1;
}