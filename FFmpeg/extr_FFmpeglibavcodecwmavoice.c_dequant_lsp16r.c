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
 int /*<<< orphan*/  dequant_lsp16i (int /*<<< orphan*/ *,double*) ; 
 int /*<<< orphan*/  dequant_lsps (double*,int,int*,int const*,int,int /*<<< orphan*/ ,double const*,double const*) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wmavoice_dq_lsp16r1 ; 
 int /*<<< orphan*/  wmavoice_dq_lsp16r2 ; 
 int /*<<< orphan*/  wmavoice_dq_lsp16r3 ; 
 float*** wmavoice_lsp16_intercoeff_a ; 
 float*** wmavoice_lsp16_intercoeff_b ; 

__attribute__((used)) static void dequant_lsp16r(GetBitContext *gb,
                           double *i_lsps, const double *old,
                           double *a1, double *a2, int q_mode)
{
    static const uint16_t vec_sizes[3] = { 128, 128, 128 };
    static const double mul_lsf[3] = {
        1.2232979501e-3,   1.4062241527e-3,   1.6114744851e-3
    };
    static const double base_lsf[3] = {
        M_PI * -5.5830e-2, M_PI * -5.2908e-2, M_PI * -5.4776e-2
    };
    const float (*ipol_tab)[2][16] = q_mode ?
        wmavoice_lsp16_intercoeff_b : wmavoice_lsp16_intercoeff_a;
    uint16_t interpol, v[3];
    int n;

    dequant_lsp16i(gb, i_lsps);

    interpol = get_bits(gb, 5);
    v[0]     = get_bits(gb, 7);
    v[1]     = get_bits(gb, 7);
    v[2]     = get_bits(gb, 7);

    for (n = 0; n < 16; n++) {
        double delta = old[n] - i_lsps[n];
        a1[n]        = ipol_tab[interpol][0][n] * delta + i_lsps[n];
        a1[16 + n]   = ipol_tab[interpol][1][n] * delta + i_lsps[n];
    }

    dequant_lsps( a2,     10,  v,     vec_sizes,    1,
                 wmavoice_dq_lsp16r1,  mul_lsf,     base_lsf);
    dequant_lsps(&a2[10], 10, &v[1], &vec_sizes[1], 1,
                 wmavoice_dq_lsp16r2, &mul_lsf[1], &base_lsf[1]);
    dequant_lsps(&a2[20], 12, &v[2], &vec_sizes[2], 1,
                 wmavoice_dq_lsp16r3, &mul_lsf[2], &base_lsf[2]);
}