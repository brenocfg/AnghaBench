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
typedef  unsigned int int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  LPC_FILTERORDER ; 
 int /*<<< orphan*/  get_lsp_poly (int*,unsigned int*) ; 
 int /*<<< orphan*/  lsf2lsp (int*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lsf2poly(int16_t *a, int16_t *lsf)
{
    int32_t f[2][6];
    int16_t lsp[10];
    int32_t tmp;
    int i;

    lsf2lsp(lsf, lsp, LPC_FILTERORDER);

    get_lsp_poly(&lsp[0], f[0]);
    get_lsp_poly(&lsp[1], f[1]);

    for (i = 5; i > 0; i--) {
        f[0][i] += (unsigned)f[0][i - 1];
        f[1][i] -= (unsigned)f[1][i - 1];
    }

    a[0] = 4096;
    for (i = 5; i > 0; i--) {
        tmp = f[0][6 - i] + (unsigned)f[1][6 - i] + 4096;
        a[6 - i] = tmp >> 13;

        tmp = f[0][6 - i] - (unsigned)f[1][6 - i] + 4096;
        a[5 + i] = tmp >> 13;
    }
}