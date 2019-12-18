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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_RB16 (int const*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int mpa_robust_parse_rtp_header(AVFormatContext *ctx,
                                       const uint8_t *buf, int len,
                                       unsigned *adu_size, unsigned *cont)
{
    unsigned header_size;

    if (len < 2) {
        av_log(ctx, AV_LOG_ERROR, "Invalid %d bytes packet\n", len);
        return AVERROR_INVALIDDATA;
    }

    *cont = !!(buf[0] & 0x80);
    if (!(buf[0] & 0x40)) {
        header_size = 1;
        *adu_size = buf[0] & ~0xc0;
    } else {
        header_size = 2;
        *adu_size = AV_RB16(buf) & ~0xc000;
    }

    return header_size;
}