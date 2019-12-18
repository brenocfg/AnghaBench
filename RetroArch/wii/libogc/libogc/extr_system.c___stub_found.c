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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static bool __stub_found()
{
	u64 sig = ((u64)(*(u32*)0x80001804) << 32) + *(u32*)0x80001808;
	if (sig == 0x5354554248415858ULL) // 'STUBHAXX'
		return true;
	return false;
}