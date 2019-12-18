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
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {TYPE_1__* item; } ;
typedef  TYPE_2__ kcdata_iter_t ;
struct TYPE_4__ {scalar_t__ size; int flags; } ;

/* Variables and functions */
 int KCDATA_FLAGS_STRUCT_HAS_PADDING ; 
 int KCDATA_FLAGS_STRUCT_PADDING_MASK ; 
 scalar_t__ kcdata_calc_padding (scalar_t__) ; 

__attribute__((used)) static inline int
kcdata_iter_is_legacy_item(kcdata_iter_t iter, uint32_t legacy_size)
{
	uint32_t legacy_size_padded = legacy_size + kcdata_calc_padding(legacy_size);
	return (iter.item->size == legacy_size_padded &&
		(iter.item->flags & (KCDATA_FLAGS_STRUCT_PADDING_MASK | KCDATA_FLAGS_STRUCT_HAS_PADDING)) == 0);

}