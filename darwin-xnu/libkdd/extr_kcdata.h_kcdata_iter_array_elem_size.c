#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {TYPE_1__* item; } ;
typedef  TYPE_2__ kcdata_iter_t ;
struct TYPE_6__ {int type; int size; } ;

/* Variables and functions */
 int KCDATA_TYPE_ARRAY ; 
 int kcdata_iter_array_elem_count (TYPE_2__) ; 
 int kcdata_iter_array_size_switch (TYPE_2__) ; 

__attribute__((used)) static inline
uint32_t kcdata_iter_array_elem_size(kcdata_iter_t iter) {
	if (iter.item->type == KCDATA_TYPE_ARRAY)
		return kcdata_iter_array_size_switch(iter);
	if (kcdata_iter_array_elem_count(iter) == 0)
		return 0;
	return (iter.item->size - (iter.item->type & 0xf)) / kcdata_iter_array_elem_count(iter);
}