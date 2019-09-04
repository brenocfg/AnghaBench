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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int LR32 (int,int) ; 
 int MASK32 ; 

__attribute__((used)) static uint64_t FLINV(uint64_t FLINV_IN, uint64_t KE)
{
    uint32_t x1, x2, k1, k2;
    x1 = FLINV_IN >> 32;
    x2 = FLINV_IN & MASK32;
    k1 = KE >> 32;
    k2 = KE & MASK32;
    x1 = x1 ^ (x2 | k2);
    x2 = x2 ^ LR32((x1 & k1), 1);
    return ((uint64_t)x1 << 32) | (uint64_t)x2;
}