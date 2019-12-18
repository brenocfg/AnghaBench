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
 int ET_DMA10_MASK ; 
 int ET_DMA10_WRAP ; 

__attribute__((used)) static inline u32 bump_fbr(u32 *fbr, u32 limit)
{
        u32 v = *fbr;
        v++;
        /* This works for all cases where limit < 1024. The 1023 case
           works because 1023++ is 1024 which means the if condition is not
           taken but the carry of the bit into the wrap bit toggles the wrap
           value correctly */
        if ((v & ET_DMA10_MASK) > limit) {
                v &= ~ET_DMA10_MASK;
                v ^= ET_DMA10_WRAP;
        }
        /* For the 1023 case */
        v &= (ET_DMA10_MASK|ET_DMA10_WRAP);
        *fbr = v;
        return v;
}