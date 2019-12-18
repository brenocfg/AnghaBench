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
 int /*<<< orphan*/  dequant_lsps (double*,int,int*,int const*,int,int /*<<< orphan*/ ,double const*,double const*) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wmavoice_dq_lsp10i ; 

__attribute__((used)) static void dequant_lsp10i(GetBitContext *gb, double *lsps)
{
    static const uint16_t vec_sizes[4] = { 256, 64, 32, 32 };
    static const double mul_lsf[4] = {
        5.2187144800e-3,    1.4626986422e-3,
        9.6179549166e-4,    1.1325736225e-3
    };
    static const double base_lsf[4] = {
        M_PI * -2.15522e-1, M_PI * -6.1646e-2,
        M_PI * -3.3486e-2,  M_PI * -5.7408e-2
    };
    uint16_t v[4];

    v[0] = get_bits(gb, 8);
    v[1] = get_bits(gb, 6);
    v[2] = get_bits(gb, 5);
    v[3] = get_bits(gb, 5);

    dequant_lsps(lsps, 10, v, vec_sizes, 4, wmavoice_dq_lsp10i,
                 mul_lsf, base_lsf);
}