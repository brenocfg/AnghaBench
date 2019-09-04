#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  chunk ;
struct TYPE_3__ {int /*<<< orphan*/  aes_ctr; } ;
typedef  TYPE_1__ MOVMuxCencContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  av_aes_ctr_crypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mov_cenc_write_encrypted(MOVMuxCencContext* ctx, AVIOContext *pb,
                                     const uint8_t *buf_in, int size)
{
    uint8_t chunk[4096];
    const uint8_t* cur_pos = buf_in;
    int size_left = size;
    int cur_size;

    while (size_left > 0) {
        cur_size = FFMIN(size_left, sizeof(chunk));
        av_aes_ctr_crypt(ctx->aes_ctr, chunk, cur_pos, cur_size);
        avio_write(pb, chunk, cur_size);
        cur_pos += cur_size;
        size_left -= cur_size;
    }
}