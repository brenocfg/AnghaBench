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
typedef  int /*<<< orphan*/  AACEncContext ;

/* Variables and functions */

void ff_aac_coder_init_mips(AACEncContext *c) {
#if HAVE_INLINE_ASM
#if !HAVE_MIPS32R6 && !HAVE_MIPS64R6
    AACCoefficientsEncoder *e = c->coder;
    int option = c->options.coder;

    if (option == 2) {
        e->quantize_and_encode_band = quantize_and_encode_band_mips;
        e->encode_window_bands_info = codebook_trellis_rate;
#if HAVE_MIPSFPU
        e->search_for_quantizers    = search_for_quantizers_twoloop;
#endif /* HAVE_MIPSFPU */
    }
#if HAVE_MIPSFPU
    e->search_for_ms            = search_for_ms_mips;
#endif /* HAVE_MIPSFPU */
#endif /* !HAVE_MIPS32R6 && !HAVE_MIPS64R6 */
#endif /* HAVE_INLINE_ASM */
}