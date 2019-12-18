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
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  auxiliary_info_add_subsample (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int mov_cenc_end_packet (int /*<<< orphan*/ *) ; 
 int mov_cenc_start_packet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mov_cenc_write_encrypted (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

int ff_mov_cenc_avc_write_nal_units(AVFormatContext *s, MOVMuxCencContext* ctx,
    int nal_length_size, AVIOContext *pb, const uint8_t *buf_in, int size)
{
    int nalsize;
    int ret;
    int j;

    ret = mov_cenc_start_packet(ctx);
    if (ret) {
        return ret;
    }

    while (size > 0) {
        /* parse the nal size */
        if (size < nal_length_size + 1) {
            av_log(s, AV_LOG_ERROR, "CENC-AVC: remaining size %d smaller than nal length+type %d\n",
                size, nal_length_size + 1);
            return -1;
        }

        avio_write(pb, buf_in, nal_length_size + 1);

        nalsize = 0;
        for (j = 0; j < nal_length_size; j++) {
            nalsize = (nalsize << 8) | *buf_in++;
        }
        size -= nal_length_size;

        /* encrypt the nal body */
        if (nalsize <= 0 || nalsize > size) {
            av_log(s, AV_LOG_ERROR, "CENC-AVC: nal size %d remaining %d\n", nalsize, size);
            return -1;
        }

        mov_cenc_write_encrypted(ctx, pb, buf_in + 1, nalsize - 1);
        buf_in += nalsize;
        size -= nalsize;

        auxiliary_info_add_subsample(ctx, nal_length_size + 1, nalsize - 1);
    }

    ret = mov_cenc_end_packet(ctx);
    if (ret) {
        return ret;
    }

    return 0;
}