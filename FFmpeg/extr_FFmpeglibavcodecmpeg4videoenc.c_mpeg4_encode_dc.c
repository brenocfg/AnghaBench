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
typedef  int /*<<< orphan*/  PutBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uni_DCtab_chrom_bits ; 
 int /*<<< orphan*/ * uni_DCtab_chrom_len ; 
 int /*<<< orphan*/ * uni_DCtab_lum_bits ; 
 int /*<<< orphan*/ * uni_DCtab_lum_len ; 

__attribute__((used)) static inline void mpeg4_encode_dc(PutBitContext *s, int level, int n)
{
    /* DC will overflow if level is outside the [-255,255] range. */
    level += 256;
    if (n < 4) {
        /* luminance */
        put_bits(s, uni_DCtab_lum_len[level], uni_DCtab_lum_bits[level]);
    } else {
        /* chrominance */
        put_bits(s, uni_DCtab_chrom_len[level], uni_DCtab_chrom_bits[level]);
    }
}