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
typedef  long long int64_t ;

/* Variables and functions */
 long long MUL64 (int,int /*<<< orphan*/ ) ; 
 int* scale_factor_modshift ; 
 int /*<<< orphan*/ ** scale_factor_mult ; 

__attribute__((used)) static inline int l1_unscale(int n, int mant, int scale_factor)
{
    int shift, mod;
    int64_t val;

    shift   = scale_factor_modshift[scale_factor];
    mod     = shift & 3;
    shift >>= 2;
    val     = MUL64((int)(mant + (-1U << n) + 1), scale_factor_mult[n-1][mod]);
    shift  += n;
    /* NOTE: at this point, 1 <= shift >= 21 + 15 */
    return (int)((val + (1LL << (shift - 1))) >> shift);
}