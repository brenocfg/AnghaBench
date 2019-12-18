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
typedef  int uint32_t ;
typedef  int int32_t ;
struct TYPE_4__ {scalar_t__ trace_enable; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ CodedBitstreamContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  ff_cbs_trace_syntax_element (TYPE_1__*,int /*<<< orphan*/ ,char const*,int const*,char*,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_bits_count (int /*<<< orphan*/ *) ; 
 int put_bits_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cbs_vp9_write_s(CodedBitstreamContext *ctx, PutBitContext *pbc,
                           int width, const char *name,
                           const int *subscripts, int32_t value)
{
    uint32_t magnitude;
    int sign;

    if (put_bits_left(pbc) < width + 1)
        return AVERROR(ENOSPC);

    sign      = value < 0;
    magnitude = sign ? -value : value;

    if (ctx->trace_enable) {
        char bits[33];
        int i;
        for (i = 0; i < width; i++)
            bits[i] = magnitude >> (width - i - 1) & 1 ? '1' : '0';
        bits[i] = sign ? '1' : '0';
        bits[i + 1] = 0;

        ff_cbs_trace_syntax_element(ctx, put_bits_count(pbc),
                                    name, subscripts, bits, value);
    }

    put_bits(pbc, width, magnitude);
    put_bits(pbc, 1, sign);

    return 0;
}