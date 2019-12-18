#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct kcdata_item {int dummy; } ;
struct TYPE_5__ {TYPE_2__* item; } ;
typedef  TYPE_1__ kcdata_iter_t ;
typedef  TYPE_2__* kcdata_item_t ;
struct TYPE_6__ {scalar_t__ size; } ;

/* Variables and functions */

__attribute__((used)) static inline
kcdata_iter_t kcdata_iter_next(kcdata_iter_t iter) {
	iter.item = (kcdata_item_t) (((uintptr_t)iter.item) + sizeof(struct kcdata_item) + (iter.item->size));
	return iter;
}