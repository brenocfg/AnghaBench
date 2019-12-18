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
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int msrle_decode_8_16_24_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int msrle_decode_pal4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ff_msrle_decode(AVCodecContext *avctx, AVFrame *pic,
                    int depth, GetByteContext *gb)
{
    switch(depth){
    case  4:
        return msrle_decode_pal4(avctx, pic, gb);
    case  8:
    case 16:
    case 24:
    case 32:
        return msrle_decode_8_16_24_32(avctx, pic, depth, gb);
    default:
        av_log(avctx, AV_LOG_ERROR, "Unknown depth %d\n", depth);
        return -1;
    }
}