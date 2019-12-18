#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_7__ {scalar_t__ trace_enable; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ CodedBitstreamContext ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_UINT_BITS (scalar_t__) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 scalar_t__ av_log2 (scalar_t__) ; 
 int cbs_av1_read_increment (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,char*,scalar_t__*) ; 
 int cbs_av1_read_ns (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,char*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int ff_cbs_read_unsigned (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,char*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_cbs_trace_syntax_element (TYPE_1__*,int,char const*,int const*,char*,scalar_t__) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cbs_av1_read_subexp(CodedBitstreamContext *ctx, GetBitContext *gbc,
                               uint32_t range_max, const char *name,
                               const int *subscripts, uint32_t *write_to)
{
    uint32_t value;
    int position, err;
    uint32_t max_len, len, range_offset, range_bits;

    if (ctx->trace_enable)
        position = get_bits_count(gbc);

    av_assert0(range_max > 0);
    max_len = av_log2(range_max - 1) - 3;

    err = cbs_av1_read_increment(ctx, gbc, 0, max_len,
                                 "subexp_more_bits", &len);
    if (err < 0)
        return err;

    if (len) {
        range_bits   = 2 + len;
        range_offset = 1 << range_bits;
    } else {
        range_bits   = 3;
        range_offset = 0;
    }

    if (len < max_len) {
        err = ff_cbs_read_unsigned(ctx, gbc, range_bits,
                                   "subexp_bits", NULL, &value,
                                   0, MAX_UINT_BITS(range_bits));
        if (err < 0)
            return err;

    } else {
        err = cbs_av1_read_ns(ctx, gbc, range_max - range_offset,
                              "subexp_final_bits", NULL, &value);
        if (err < 0)
            return err;
    }
    value += range_offset;

    if (ctx->trace_enable)
        ff_cbs_trace_syntax_element(ctx, position,
                                    name, subscripts, "", value);

    *write_to = value;
    return err;
}