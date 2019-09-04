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
typedef  scalar_t__ mach_voucher_attr_key_t ;
typedef  scalar_t__ iv_index_t ;

/* Variables and functions */
 scalar_t__ IV_UNUSED_KEYINDEX ; 
 scalar_t__ MACH_VOUCHER_ATTR_KEY_ALL ; 
 scalar_t__ MACH_VOUCHER_ATTR_KEY_NUM_WELL_KNOWN ; 

__attribute__((used)) static inline iv_index_t
iv_key_to_index(mach_voucher_attr_key_t key)
{
	if (MACH_VOUCHER_ATTR_KEY_ALL == key ||
	    MACH_VOUCHER_ATTR_KEY_NUM_WELL_KNOWN < key)
		return IV_UNUSED_KEYINDEX;
	return (iv_index_t)key - 1;
}