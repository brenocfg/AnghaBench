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
struct TYPE_5__ {int /*<<< orphan*/  huff_buffer; } ;
struct TYPE_4__ {int mb_width; int width; int mb_height; int height; int chroma_format; TYPE_2__* mjpeg_ctx; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  int /*<<< orphan*/  MJpegHuffmanCode ;
typedef  TYPE_2__ MJpegContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  CHROMA_420 130 
#define  CHROMA_422 129 
#define  CHROMA_444 128 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_malloc_array (size_t,int) ; 

__attribute__((used)) static int alloc_huffman(MpegEncContext *s)
{
    MJpegContext *m = s->mjpeg_ctx;
    size_t num_mbs, num_blocks, num_codes;
    int blocks_per_mb;

    // We need to init this here as the mjpeg init is called before the common init,
    s->mb_width  = (s->width  + 15) / 16;
    s->mb_height = (s->height + 15) / 16;

    switch (s->chroma_format) {
    case CHROMA_420: blocks_per_mb =  6; break;
    case CHROMA_422: blocks_per_mb =  8; break;
    case CHROMA_444: blocks_per_mb = 12; break;
    default: av_assert0(0);
    };

    // Make sure we have enough space to hold this frame.
    num_mbs = s->mb_width * s->mb_height;
    num_blocks = num_mbs * blocks_per_mb;
    num_codes = num_blocks * 64;

    m->huff_buffer = av_malloc_array(num_codes, sizeof(MJpegHuffmanCode));
    if (!m->huff_buffer)
        return AVERROR(ENOMEM);
    return 0;
}