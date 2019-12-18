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
struct bcm5974_param {int dim; int devmax; int devmin; } ;

/* Variables and functions */

__attribute__((used)) static inline int int2scale(const struct bcm5974_param *p, int x)
{
	return x * p->dim / (p->devmax - p->devmin);
}