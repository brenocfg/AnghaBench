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
typedef  int /*<<< orphan*/  PutBitContext ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  FIRST_DC_CB ; 
 int GET_SIGN (int) ; 
 int MAKE_CODE (int) ; 
 int /*<<< orphan*/  encode_vlc_codeword (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ff_prores_dc_codebook ; 

__attribute__((used)) static void encode_dcs(PutBitContext *pb, int16_t *blocks,
                       int blocks_per_slice, int scale)
{
    int i;
    int codebook = 3, code, dc, prev_dc, delta, sign, new_sign;

    prev_dc = (blocks[0] - 0x4000) / scale;
    encode_vlc_codeword(pb, FIRST_DC_CB, MAKE_CODE(prev_dc));
    sign     = 0;
    codebook = 3;
    blocks  += 64;

    for (i = 1; i < blocks_per_slice; i++, blocks += 64) {
        dc       = (blocks[0] - 0x4000) / scale;
        delta    = dc - prev_dc;
        new_sign = GET_SIGN(delta);
        delta    = (delta ^ sign) - sign;
        code     = MAKE_CODE(delta);
        encode_vlc_codeword(pb, ff_prores_dc_codebook[codebook], code);
        codebook = (code + (code & 1)) >> 1;
        codebook = FFMIN(codebook, 3);
        sign     = new_sign;
        prev_dc  = dc;
    }
}