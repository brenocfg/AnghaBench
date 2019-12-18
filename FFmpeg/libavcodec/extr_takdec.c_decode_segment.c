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
struct CParam {int init; unsigned int escape; unsigned int aescape; unsigned int scale; scalar_t__ bias; } ;
typedef  int int8_t ;
typedef  unsigned int int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ TAKDecContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int FF_ARRAY_ELEMS (struct CParam*) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_long (int /*<<< orphan*/ *,int) ; 
 unsigned int get_unary (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,int) ; 
 struct CParam* xcodes ; 

__attribute__((used)) static int decode_segment(TAKDecContext *s, int8_t mode, int32_t *decoded, int len)
{
    struct CParam code;
    GetBitContext *gb = &s->gb;
    int i;

    if (!mode) {
        memset(decoded, 0, len * sizeof(*decoded));
        return 0;
    }

    if (mode > FF_ARRAY_ELEMS(xcodes))
        return AVERROR_INVALIDDATA;
    code = xcodes[mode - 1];

    for (i = 0; i < len; i++) {
        unsigned x = get_bits_long(gb, code.init);
        if (x >= code.escape && get_bits1(gb)) {
            x |= 1 << code.init;
            if (x >= code.aescape) {
                unsigned scale = get_unary(gb, 1, 9);
                if (scale == 9) {
                    int scale_bits = get_bits(gb, 3);
                    if (scale_bits > 0) {
                        if (scale_bits == 7) {
                            scale_bits += get_bits(gb, 5);
                            if (scale_bits > 29)
                                return AVERROR_INVALIDDATA;
                        }
                        scale = get_bits_long(gb, scale_bits) + 1;
                        x    += code.scale * scale;
                    }
                    x += code.bias;
                } else
                    x += code.scale * scale - code.escape;
            } else
                x -= code.escape;
        }
        decoded[i] = (x >> 1) ^ -(x & 1);
    }

    return 0;
}