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

/* Variables and functions */
 long vpa_call (int,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline long unregister_dtl(unsigned long cpu)
{
	return vpa_call(0x6, cpu, 0);
}