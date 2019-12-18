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

/* Variables and functions */
 int ROT (int,int) ; 

__attribute__((used)) static inline uint64_t update_h2(uint64_t k, uint64_t h1, uint64_t h2)
{
    k ^= h2;
    k = ROT(k, 31);
    k += h1;
    k *= 5;
    k += 0x38495ab5;
    return k;
}