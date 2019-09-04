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
 int auxiliary_info_add_subsample (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mov_cenc_end_packet (int /*<<< orphan*/ *) ; 
 int mov_cenc_start_packet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mov_cenc_write_encrypted (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

int ff_mov_cenc_write_packet(MOVMuxCencContext* ctx, AVIOContext *pb,
                          const uint8_t *buf_in, int size)
{
    int ret;

    ret = mov_cenc_start_packet(ctx);
    if (ret) {
        return ret;
    }

    ret = auxiliary_info_add_subsample(ctx, 0, size);
    if (ret) {
        return ret;
    }

    mov_cenc_write_encrypted(ctx, pb, buf_in, size);

    ret = mov_cenc_end_packet(ctx);
    if (ret) {
        return ret;
    }

    return 0;
}