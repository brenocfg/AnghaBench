#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  block_len; int /*<<< orphan*/ * max_exponent; int /*<<< orphan*/ * exponents; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ WMACodecContext ;

/* Variables and functions */
 int NB_LSP_COEFS ; 
 float** ff_wma_lsp_codebook ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wma_lsp_to_curve (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,float*) ; 

__attribute__((used)) static void decode_exp_lsp(WMACodecContext *s, int ch)
{
    float lsp_coefs[NB_LSP_COEFS];
    int val, i;

    for (i = 0; i < NB_LSP_COEFS; i++) {
        if (i == 0 || i >= 8)
            val = get_bits(&s->gb, 3);
        else
            val = get_bits(&s->gb, 4);
        lsp_coefs[i] = ff_wma_lsp_codebook[i][val];
    }

    wma_lsp_to_curve(s, s->exponents[ch], &s->max_exponent[ch],
                     s->block_len, lsp_coefs);
}