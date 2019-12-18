#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int extradata_size; int /*<<< orphan*/  extradata; } ;
struct TYPE_5__ {int* data; unsigned int size; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memmove (int*,int*,unsigned int) ; 

__attribute__((used)) static int xvid_strip_vol_header(AVCodecContext *avctx, AVPacket *pkt,
                                 unsigned int header_len,
                                 unsigned int frame_len)
{
    int vo_len = 0, i;

    for (i = 0; i < header_len - 3; i++) {
        if (pkt->data[i]     == 0x00 &&
            pkt->data[i + 1] == 0x00 &&
            pkt->data[i + 2] == 0x01 &&
            pkt->data[i + 3] == 0xB6) {
            vo_len = i;
            break;
        }
    }

    if (vo_len > 0) {
        /* We need to store the header, so extract it */
        if (!avctx->extradata) {
            avctx->extradata = av_malloc(vo_len);
            if (!avctx->extradata)
                return AVERROR(ENOMEM);
            memcpy(avctx->extradata, pkt->data, vo_len);
            avctx->extradata_size = vo_len;
        }
        /* Less dangerous now, memmove properly copies the two
         * chunks of overlapping data */
        memmove(pkt->data, &pkt->data[vo_len], frame_len - vo_len);
        pkt->size = frame_len - vo_len;
    }
    return 0;
}