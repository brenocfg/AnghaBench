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
struct ioc {scalar_t__ res_map; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long ptr_to_pide(struct ioc *ioc, unsigned long *res_ptr,
				 unsigned int bitshiftcnt)
{
	return (((unsigned long)res_ptr - (unsigned long)ioc->res_map) << 3)
		+ bitshiftcnt;
}