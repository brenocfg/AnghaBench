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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
#define  M_PI 128 
 int /*<<< orphan*/  dequant_lsp10i (int /*<<< orphan*/ *,double*) ; 
 int /*<<< orphan*/  dequant_lsps (double*,int,int*,int const*,int,int /*<<< orphan*/ ,double const*,double const*) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wmavoice_dq_lsp10r ; 
 float*** wmavoice_lsp10_intercoeff_a ; 
 float*** wmavoice_lsp10_intercoeff_b ; 

__attribute__((used)) static void dequant_lsp10r(GetBitContext *gb,
                           double *i_lsps, const double *old,
                           double *a1, double *a2, int q_mode)
{
    static const uint16_t vec_sizes[3] = { 128, 64, 64 };
    static const double mul_lsf[3] = {
        2.5807601174e-3,    1.2354460219e-3,   1.1763821673e-3
    };
    static const double base_lsf[3] = {
        M_PI * -1.07448e-1, M_PI * -5.2706e-2, M_PI * -5.1634e-2
    };
    const float (*ipol_tab)[2][10] = q_mode ?
        wmavoice_lsp10_intercoeff_b : wmavoice_lsp10_intercoeff_a;
    uint16_t interpol, v[3];
    int n;

    dequant_lsp10i(gb, i_lsps);

    interpol = get_bits(gb, 5);
    v[0]     = get_bits(gb, 7);
    v[1]     = get_bits(gb, 6);
    v[2]     = get_bits(gb, 6);

    for (n = 0; n < 10; n++) {
        double delta = old[n] - i_lsps[n];
        a1[n]        = ipol_tab[interpol][0][n] * delta + i_lsps[n];
        a1[10 + n]   = ipol_tab[interpol][1][n] * delta + i_lsps[n];
    }

    dequant_lsps(a2, 20, v, vec_sizes, 3, wmavoice_dq_lsp10r,
                 mul_lsf, base_lsf);
}