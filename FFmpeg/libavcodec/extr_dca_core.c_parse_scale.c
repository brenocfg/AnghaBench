#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ DCACoreDecoder ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 unsigned int FF_ARRAY_ELEMS (int*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dca_get_vlc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int* ff_dca_scale_factor_quant6 ; 
 int* ff_dca_scale_factor_quant7 ; 
 int /*<<< orphan*/  ff_dca_vlc_scale_factor ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int parse_scale(DCACoreDecoder *s, int *scale_index, int sel)
{
    const uint32_t *scale_table;
    unsigned int scale_size;

    // Select the root square table
    if (sel > 5) {
        scale_table = ff_dca_scale_factor_quant7;
        scale_size = FF_ARRAY_ELEMS(ff_dca_scale_factor_quant7);
    } else {
        scale_table = ff_dca_scale_factor_quant6;
        scale_size = FF_ARRAY_ELEMS(ff_dca_scale_factor_quant6);
    }

    // If Huffman code was used, the difference of scales was encoded
    if (sel < 5)
        *scale_index += dca_get_vlc(&s->gb, &ff_dca_vlc_scale_factor, sel);
    else
        *scale_index = get_bits(&s->gb, sel + 1);

    // Look up scale factor from the root square table
    if ((unsigned int)*scale_index >= scale_size) {
        av_log(s->avctx, AV_LOG_ERROR, "Invalid scale factor index\n");
        return AVERROR_INVALIDDATA;
    }

    return scale_table[*scale_index];
}