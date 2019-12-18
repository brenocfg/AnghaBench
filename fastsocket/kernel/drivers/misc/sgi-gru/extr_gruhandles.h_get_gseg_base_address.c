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
 int GRU_GSEG0_BASE ; 
 int GRU_GSEG_STRIDE ; 

__attribute__((used)) static inline void *get_gseg_base_address(void *base, int ctxnum)
{
	return (void *)(base + GRU_GSEG0_BASE + GRU_GSEG_STRIDE * ctxnum);
}