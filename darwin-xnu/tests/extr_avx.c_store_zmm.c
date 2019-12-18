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
typedef  int /*<<< orphan*/  VECTOR512 ;

/* Variables and functions */

__attribute__((used)) static inline void
store_zmm(VECTOR512 *vecarray) {
	int i = 0;
	    __asm__ volatile("vmovaps  %%zmm0, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm1, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm2, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm3, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm4, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm5, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm6, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm7, %0" :"=m" (vecarray[i]));
#if defined(__x86_64__)
	i++;__asm__ volatile("vmovaps  %%zmm8, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm9, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm10, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm11, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm12, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm13, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm14, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm15, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm16, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm17, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm18, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm19, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm20, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm21, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm22, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm23, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm24, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm25, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm26, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm27, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm28, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm29, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm30, %0" :"=m" (vecarray[i]));
	i++;__asm__ volatile("vmovaps  %%zmm31, %0" :"=m" (vecarray[i]));
#endif
}