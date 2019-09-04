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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WB32 (int /*<<< orphan*/ *,int) ; 
 int avio_rl32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xmv_read_extradata(uint8_t *extradata, AVIOContext *pb)
{
    /* Read the XMV extradata */

    uint32_t data = avio_rl32(pb);

    int mspel_bit        = !!(data & 0x01);
    int loop_filter      = !!(data & 0x02);
    int abt_flag         = !!(data & 0x04);
    int j_type_bit       = !!(data & 0x08);
    int top_left_mv_flag = !!(data & 0x10);
    int per_mb_rl_bit    = !!(data & 0x20);
    int slice_count      = (data >> 6) & 7;

    /* Write it back as standard WMV2 extradata */

    data = 0;

    data |= mspel_bit        << 15;
    data |= loop_filter      << 14;
    data |= abt_flag         << 13;
    data |= j_type_bit       << 12;
    data |= top_left_mv_flag << 11;
    data |= per_mb_rl_bit    << 10;
    data |= slice_count      <<  7;

    AV_WB32(extradata, data);
}