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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AV_PIX_FMT_RGB24 ; 
 int /*<<< orphan*/  dx2_decode_slice_555 ; 
 int /*<<< orphan*/  dx2_decode_slice_565 ; 
 int dxtory_decode_v2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setup_lru_555 ; 
 int /*<<< orphan*/  setup_lru_565 ; 

__attribute__((used)) static int dxtory_decode_v2_565(AVCodecContext *avctx, AVFrame *pic,
                                const uint8_t *src, int src_size, int is_565)
{
    enum AVPixelFormat fmt = AV_PIX_FMT_RGB24;
    if (is_565)
        return dxtory_decode_v2(avctx, pic, src, src_size,
                                dx2_decode_slice_565,
                                setup_lru_565,
                                fmt);
    else
        return dxtory_decode_v2(avctx, pic, src, src_size,
                                dx2_decode_slice_555,
                                setup_lru_555,
                                fmt);
}