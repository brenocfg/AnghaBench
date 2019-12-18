#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  avctx; } ;
struct TYPE_5__ {unsigned int mb_width; unsigned int mb_height; unsigned int bitmask_size; int* mxm_bitmask; int* completion_bitmask; int got_mxm_bitmask; int has_complete_frame; TYPE_1__ jpg; } ;
typedef  TYPE_2__ MXpegDecodeContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 void* AV_RL16 (int const*) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (int**) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int* av_malloc (unsigned int) ; 
 int* av_mallocz (unsigned int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,unsigned int) ; 

__attribute__((used)) static int mxpeg_decode_mxm(MXpegDecodeContext *s,
                            const uint8_t *buf_ptr, int buf_size)
{
    unsigned bitmask_size, mb_count;
    int i;

    s->mb_width  = AV_RL16(buf_ptr+4);
    s->mb_height = AV_RL16(buf_ptr+6);
    mb_count = s->mb_width * s->mb_height;

    bitmask_size = (mb_count + 7) >> 3;
    if (bitmask_size > buf_size - 12) {
        av_log(s->jpg.avctx, AV_LOG_ERROR,
               "MXM bitmask is not complete\n");
        return AVERROR(EINVAL);
    }

    if (s->bitmask_size != bitmask_size) {
        s->bitmask_size = 0;
        av_freep(&s->mxm_bitmask);
        s->mxm_bitmask = av_malloc(bitmask_size);
        if (!s->mxm_bitmask) {
            av_log(s->jpg.avctx, AV_LOG_ERROR,
                   "MXM bitmask memory allocation error\n");
            return AVERROR(ENOMEM);
        }

        av_freep(&s->completion_bitmask);
        s->completion_bitmask = av_mallocz(bitmask_size);
        if (!s->completion_bitmask) {
            av_log(s->jpg.avctx, AV_LOG_ERROR,
                   "Completion bitmask memory allocation error\n");
            return AVERROR(ENOMEM);
        }

        s->bitmask_size = bitmask_size;
    }

    memcpy(s->mxm_bitmask, buf_ptr + 12, bitmask_size);
    s->got_mxm_bitmask = 1;

    if (!s->has_complete_frame) {
        uint8_t completion_check = 0xFF;
        for (i = 0; i < bitmask_size; ++i) {
            s->completion_bitmask[i] |= s->mxm_bitmask[i];
            completion_check &= s->completion_bitmask[i];
        }
        s->has_complete_frame = !(completion_check ^ 0xFF);
    }

    return 0;
}