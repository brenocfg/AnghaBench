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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static inline int in_scope(u32 domain, u32 addr)
{
	if (!domain || (domain == addr))
		return 1;
	if (domain == (addr & 0xfffff000u)) /* domain <Z.C.0> */
		return 1;
	if (domain == (addr & 0xff000000u)) /* domain <Z.0.0> */
		return 1;
	return 0;
}