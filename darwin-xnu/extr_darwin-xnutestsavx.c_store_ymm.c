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
typedef  int /*<<< orphan*/  VECTOR256 ;

/* Variables and functions */

__attribute__((used)) static inline void
store_ymm(VECTOR256 *vec256array) {
	int i = 0;
	    __asm__ volatile("vmovaps  %%ymm0, %0" :"=m" (vec256array[i]));
	i++;__asm__ volatile("vmovaps  %%ymm1, %0" :"=m" (vec256array[i]));
	i++;__asm__ volatile("vmovaps  %%ymm2, %0" :"=m" (vec256array[i]));
	i++;__asm__ volatile("vmovaps  %%ymm3, %0" :"=m" (vec256array[i]));
	i++;__asm__ volatile("vmovaps  %%ymm4, %0" :"=m" (vec256array[i]));
	i++;__asm__ volatile("vmovaps  %%ymm5, %0" :"=m" (vec256array[i]));
	i++;__asm__ volatile("vmovaps  %%ymm6, %0" :"=m" (vec256array[i]));
	i++;__asm__ volatile("vmovaps  %%ymm7, %0" :"=m" (vec256array[i]));
#if defined(__x86_64__)
	i++;__asm__ volatile("vmovaps  %%ymm8, %0" :"=m" (vec256array[i]));
	i++;__asm__ volatile("vmovaps  %%ymm9, %0" :"=m" (vec256array[i]));
	i++;__asm__ volatile("vmovaps  %%ymm10, %0" :"=m" (vec256array[i]));
	i++;__asm__ volatile("vmovaps  %%ymm11, %0" :"=m" (vec256array[i]));
	i++;__asm__ volatile("vmovaps  %%ymm12, %0" :"=m" (vec256array[i]));
	i++;__asm__ volatile("vmovaps  %%ymm13, %0" :"=m" (vec256array[i]));
	i++;__asm__ volatile("vmovaps  %%ymm14, %0" :"=m" (vec256array[i]));
	i++;__asm__ volatile("vmovaps  %%ymm15, %0" :"=m" (vec256array[i]));
#endif
}