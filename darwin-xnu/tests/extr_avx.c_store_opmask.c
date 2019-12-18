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
typedef  int /*<<< orphan*/  OPMASK ;

/* Variables and functions */

__attribute__((used)) static inline void
store_opmask(OPMASK k[]) {
	__asm__ volatile("kmovq %%k0, %0" :"=m" (k[0]));
	__asm__ volatile("kmovq %%k1, %0" :"=m" (k[1]));
	__asm__ volatile("kmovq %%k2, %0" :"=m" (k[2]));
	__asm__ volatile("kmovq %%k3, %0" :"=m" (k[3]));
	__asm__ volatile("kmovq %%k4, %0" :"=m" (k[4]));
	__asm__ volatile("kmovq %%k5, %0" :"=m" (k[5]));
	__asm__ volatile("kmovq %%k6, %0" :"=m" (k[6]));
	__asm__ volatile("kmovq %%k7, %0" :"=m" (k[7]));
}