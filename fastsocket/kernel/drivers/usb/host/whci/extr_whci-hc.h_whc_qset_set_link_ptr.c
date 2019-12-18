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
typedef  int u64 ;

/* Variables and functions */
 int QH_LINK_PTR (int) ; 
 int QH_LINK_PTR_MASK ; 
 int QH_LINK_T ; 

__attribute__((used)) static inline void whc_qset_set_link_ptr(u64 *ptr, u64 target)
{
	if (target)
		*ptr = (*ptr & ~(QH_LINK_PTR_MASK | QH_LINK_T)) | QH_LINK_PTR(target);
	else
		*ptr = QH_LINK_T;
}