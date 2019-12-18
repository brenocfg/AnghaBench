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
typedef  int /*<<< orphan*/  MOVMuxCencContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  auxiliary_info_add_subsample (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ff_avc_find_startcode (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int mov_cenc_end_packet (int /*<<< orphan*/ *) ; 
 int mov_cenc_start_packet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mov_cenc_write_encrypted (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

int ff_mov_cenc_avc_parse_nal_units(MOVMuxCencContext* ctx, AVIOContext *pb,
                                 const uint8_t *buf_in, int size)
{
    const uint8_t *p = buf_in;
    const uint8_t *end = p + size;
    const uint8_t *nal_start, *nal_end;
    int ret;

    ret = mov_cenc_start_packet(ctx);
    if (ret) {
        return ret;
    }

    size = 0;
    nal_start = ff_avc_find_startcode(p, end);
    for (;;) {
        while (nal_start < end && !*(nal_start++));
        if (nal_start == end)
            break;

        nal_end = ff_avc_find_startcode(nal_start, end);

        avio_wb32(pb, nal_end - nal_start);
        avio_w8(pb, *nal_start);
        mov_cenc_write_encrypted(ctx, pb, nal_start + 1, nal_end - nal_start - 1);

        auxiliary_info_add_subsample(ctx, 5, nal_end - nal_start - 1);

        size += 4 + nal_end - nal_start;
        nal_start = nal_end;
    }

    ret = mov_cenc_end_packet(ctx);
    if (ret) {
        return ret;
    }

    return size;
}