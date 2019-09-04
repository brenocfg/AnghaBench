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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 size_t* ff_zigzag_direct ; 
 size_t* ff_zigzag_scan ; 
 int /*<<< orphan*/  get_bits1 (int /*<<< orphan*/ *) ; 
 int get_se_golomb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t const*,int) ; 

__attribute__((used)) static int decode_scaling_list(GetBitContext *gb, uint8_t *factors, int size,
                                const uint8_t *jvt_list,
                                const uint8_t *fallback_list)
{
    int i, last = 8, next = 8;
    const uint8_t *scan = size == 16 ? ff_zigzag_scan : ff_zigzag_direct;
    if (!get_bits1(gb)) /* matrix not written, we use the predicted one */
        memcpy(factors, fallback_list, size * sizeof(uint8_t));
    else
        for (i = 0; i < size; i++) {
            if (next) {
                int v = get_se_golomb(gb);
                if (v < -128 || v > 127) {
                    av_log(NULL, AV_LOG_ERROR, "delta scale %d is invalid\n", v);
                    return AVERROR_INVALIDDATA;
                }
                next = (last + v) & 0xff;
            }
            if (!i && !next) { /* matrix not written, we use the preset one */
                memcpy(factors, jvt_list, size * sizeof(uint8_t));
                break;
            }
            last = factors[scan[i]] = next ? next : last;
        }
    return 0;
}