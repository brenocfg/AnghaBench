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
struct i5400_error_info {int nrecmemb; } ;

/* Variables and functions */

__attribute__((used)) static inline int nrec_cas(struct i5400_error_info *info)
{
	return ((info->nrecmemb) >> 16) & 0x1fff;
}