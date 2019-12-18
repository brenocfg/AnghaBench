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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int** mpc8_cnk ; 
 int mpc8_dec_base (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline int mpc8_dec_enum(GetBitContext *gb, int k, int n)
{
    int bits = 0;
    const uint32_t * C = mpc8_cnk[k-1];
    int code = mpc8_dec_base(gb, k, n);

    do {
        n--;
        if (code >= C[n]) {
            bits |= 1U << n;
            code -= C[n];
            C -= 32;
            k--;
        }
    } while(k > 0);

    return bits;
}