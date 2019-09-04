#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
struct TYPE_5__ {scalar_t__ trace_enable; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ CodedBitstreamContext ;

/* Variables and functions */
 int av_log2 (int) ; 
 int /*<<< orphan*/  ff_cbs_trace_syntax_element (TYPE_1__*,int,char const*,int /*<<< orphan*/ *,char*,int) ; 
 int ff_cbs_write_unsigned (TYPE_1__*,int /*<<< orphan*/ *,int,char*,int*,int,int,int) ; 
 int put_bits_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cbs_av1_write_leb128(CodedBitstreamContext *ctx, PutBitContext *pbc,
                                const char *name, uint64_t value)
{
    int position, err, len, i;
    uint8_t byte;

    len = (av_log2(value) + 7) / 7;

    if (ctx->trace_enable)
        position = put_bits_count(pbc);

    for (i = 0; i < len; i++) {
        int subscript[2] = { 1, i };

        byte = value >> (7 * i) & 0x7f;
        if (i < len - 1)
            byte |= 0x80;

        err = ff_cbs_write_unsigned(ctx, pbc, 8, "leb128_byte[i]", subscript,
                                    byte, 0x00, 0xff);
        if (err < 0)
            return err;
    }

    if (ctx->trace_enable)
        ff_cbs_trace_syntax_element(ctx, position, name, NULL, "", value);

    return 0;
}