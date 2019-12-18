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
typedef  int __s32 ;

/* Variables and functions */

__attribute__((used)) static inline void stride_align(__s32 *width)
{
	if (((*width + 7) &  ~7) < 4096)
		*width = (*width + 7) &  ~7;
	else
		*width = *width &  ~7;
}