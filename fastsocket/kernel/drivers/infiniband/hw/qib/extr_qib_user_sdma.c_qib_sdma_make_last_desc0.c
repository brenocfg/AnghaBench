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
typedef  int __le64 ;

/* Variables and functions */
 int cpu_to_le64 (unsigned long long) ; 

__attribute__((used)) static inline __le64 qib_sdma_make_last_desc0(__le64 descq)
{
					      /* last */  /* dma head */
	return descq | cpu_to_le64(1ULL << 11 | 1ULL << 13);
}