#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kcdata_item {int dummy; } ;
struct TYPE_5__ {scalar_t__ end; TYPE_1__* item; } ;
typedef  TYPE_2__ kcdata_iter_t ;
struct TYPE_4__ {uintptr_t size; } ;

/* Variables and functions */

__attribute__((used)) static inline
int kcdata_iter_valid(kcdata_iter_t iter) {
	return
		( (uintptr_t)iter.item + sizeof(struct kcdata_item) <= (uintptr_t)iter.end ) &&
		( (uintptr_t)iter.item + sizeof(struct kcdata_item) + iter.item->size  <= (uintptr_t)iter.end);
}