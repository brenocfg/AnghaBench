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
typedef  size_t u16 ;
struct cpu_rmap {scalar_t__ used; scalar_t__ size; void** obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

int cpu_rmap_add(struct cpu_rmap *rmap, void *obj)
{
	u16 index;

	BUG_ON(rmap->used >= rmap->size);
	index = rmap->used++;
	rmap->obj[index] = obj;
	return index;
}