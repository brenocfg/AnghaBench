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
typedef  int /*<<< orphan*/  bits ;
struct TYPE_4__ {scalar_t__ trace_enable; int /*<<< orphan*/  log_ctx; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ CodedBitstreamContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  ff_cbs_trace_syntax_element (TYPE_1__*,int,char const*,int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cbs_vp9_read_increment(CodedBitstreamContext *ctx, GetBitContext *gbc,
                                  uint32_t range_min, uint32_t range_max,
                                  const char *name, uint32_t *write_to)
{
    uint32_t value;
    int position, i;
    char bits[8];

    av_assert0(range_min <= range_max && range_max - range_min < sizeof(bits) - 1);
    if (ctx->trace_enable)
        position = get_bits_count(gbc);

    for (i = 0, value = range_min; value < range_max;) {
        if (get_bits_left(gbc) < 1) {
            av_log(ctx->log_ctx, AV_LOG_ERROR, "Invalid increment value at "
                   "%s: bitstream ended.\n", name);
            return AVERROR_INVALIDDATA;
        }
        if (get_bits1(gbc)) {
            bits[i++] = '1';
            ++value;
        } else {
            bits[i++] = '0';
            break;
        }
    }

    if (ctx->trace_enable) {
        bits[i] = 0;
        ff_cbs_trace_syntax_element(ctx, position, name, NULL, bits, value);
    }

    *write_to = value;
    return 0;
}