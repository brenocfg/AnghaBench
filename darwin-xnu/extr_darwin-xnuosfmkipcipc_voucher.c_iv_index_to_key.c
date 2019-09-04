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
typedef  int /*<<< orphan*/  mach_voucher_attr_key_t ;
typedef  size_t iv_index_t ;
struct TYPE_2__ {int /*<<< orphan*/  ivgte_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  MACH_VOUCHER_ATTR_KEY_NONE ; 
 size_t MACH_VOUCHER_ATTR_KEY_NUM_WELL_KNOWN ; 
 TYPE_1__* iv_global_table ; 

__attribute__((used)) static inline mach_voucher_attr_key_t
iv_index_to_key(iv_index_t key_index)
{
	if (MACH_VOUCHER_ATTR_KEY_NUM_WELL_KNOWN > key_index)
		return iv_global_table[key_index].ivgte_key;
	return MACH_VOUCHER_ATTR_KEY_NONE;
		
}