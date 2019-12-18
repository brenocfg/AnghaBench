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
struct TYPE_4__ {scalar_t__ trace_enable; int /*<<< orphan*/  log_ctx; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ CodedBitstreamContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  ff_cbs_trace_syntax_element (TYPE_1__*,int,char const*,int const*,char*,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cbs_vp9_read_le(CodedBitstreamContext *ctx, GetBitContext *gbc,
                           int width, const char *name,
                           const int *subscripts, uint32_t *write_to)
{
    uint32_t value;
    int position, b;

    av_assert0(width % 8 == 0);

    if (ctx->trace_enable)
        position = get_bits_count(gbc);

    if (get_bits_left(gbc) < width) {
        av_log(ctx->log_ctx, AV_LOG_ERROR, "Invalid le value at "
               "%s: bitstream ended.\n", name);
        return AVERROR_INVALIDDATA;
    }

    value = 0;
    for (b = 0; b < width; b += 8)
        value |= get_bits(gbc, 8) << b;

    if (ctx->trace_enable) {
        char bits[33];
        int i;
        for (b = 0; b < width; b += 8)
            for (i = 0; i < 8; i++)
                bits[b + i] = value >> (b + i) & 1 ? '1' : '0';
        bits[b] = 0;

        ff_cbs_trace_syntax_element(ctx, position, name, subscripts,
                                    bits, value);
    }

    *write_to = value;
    return 0;
}