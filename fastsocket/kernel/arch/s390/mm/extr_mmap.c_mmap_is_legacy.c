#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int personality; TYPE_2__* signal; } ;
struct TYPE_5__ {TYPE_1__* rlim; } ;
struct TYPE_4__ {scalar_t__ rlim_cur; } ;

/* Variables and functions */
 int ADDR_COMPAT_LAYOUT ; 
 size_t RLIMIT_STACK ; 
 scalar_t__ RLIM_INFINITY ; 
 TYPE_3__* current ; 
 int sysctl_legacy_va_layout ; 

__attribute__((used)) static inline int mmap_is_legacy(void)
{
	if (current->personality & ADDR_COMPAT_LAYOUT)
		return 1;
	if (current->signal->rlim[RLIMIT_STACK].rlim_cur == RLIM_INFINITY)
		return 1;
	return sysctl_legacy_va_layout;
}