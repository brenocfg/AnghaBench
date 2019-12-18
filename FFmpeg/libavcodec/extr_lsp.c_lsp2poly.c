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
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  FRAC_BITS ; 
 int MULL (int,int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lsp2poly(int* f, const int16_t* lsp, int lp_half_order)
{
    int i, j;

    f[0] = 0x400000;          // 1.0 in (3.22)
    f[1] = -lsp[0] * 256;     // *2 and (0.15) -> (3.22)

    for(i=2; i<=lp_half_order; i++)
    {
        f[i] = f[i-2];
        for(j=i; j>1; j--)
            f[j] -= MULL(f[j-1], lsp[2*i-2], FRAC_BITS) - f[j-2];

        f[1] -= lsp[2*i-2] * 256;
    }
}