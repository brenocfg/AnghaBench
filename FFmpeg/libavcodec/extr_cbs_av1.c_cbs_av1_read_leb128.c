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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_5__ {scalar_t__ trace_enable; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ CodedBitstreamContext ;

/* Variables and functions */
 int ff_cbs_read_unsigned (TYPE_1__*,int /*<<< orphan*/ *,int,char*,int*,int*,int,int) ; 
 int /*<<< orphan*/  ff_cbs_trace_syntax_element (TYPE_1__*,int,char const*,int /*<<< orphan*/ *,char*,int) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cbs_av1_read_leb128(CodedBitstreamContext *ctx, GetBitContext *gbc,
                               const char *name, uint64_t *write_to)
{
    uint64_t value;
    int position, err, i;

    if (ctx->trace_enable)
        position = get_bits_count(gbc);

    value = 0;
    for (i = 0; i < 8; i++) {
        int subscript[2] = { 1, i };
        uint32_t byte;
        err = ff_cbs_read_unsigned(ctx, gbc, 8, "leb128_byte[i]", subscript,
                                   &byte, 0x00, 0xff);
        if (err < 0)
            return err;

        value |= (uint64_t)(byte & 0x7f) << (i * 7);
        if (!(byte & 0x80))
            break;
    }

    if (ctx->trace_enable)
        ff_cbs_trace_syntax_element(ctx, position, name, NULL, "", value);

    *write_to = value;
    return 0;
}