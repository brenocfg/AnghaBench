#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_9__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_8__ {int depth; } ;
struct TYPE_7__ {float re; } ;
typedef  TYPE_1__ FFTComplex ;
typedef  TYPE_2__ ConvolveContext ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  av_clip (float,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  av_clip_uint8 (float) ; 

__attribute__((used)) static void get_output(ConvolveContext *s, FFTComplex *input, AVFrame *out,
                       int w, int h, int n, int plane, float scale)
{
    const int max = (1 << s->depth) - 1;
    const int hh = h / 2;
    const int hw = w / 2;
    int y, x;

    if (s->depth == 8) {
        for (y = 0; y < hh; y++) {
            uint8_t *dst = out->data[plane] + (y + hh) * out->linesize[plane] + hw;
            for (x = 0; x < hw; x++)
                dst[x] = av_clip_uint8(input[y * n + x].re * scale);
        }
        for (y = 0; y < hh; y++) {
            uint8_t *dst = out->data[plane] + (y + hh) * out->linesize[plane];
            for (x = 0; x < hw; x++)
                dst[x] = av_clip_uint8(input[y * n + n - hw + x].re * scale);
        }
        for (y = 0; y < hh; y++) {
            uint8_t *dst = out->data[plane] + y * out->linesize[plane] + hw;
            for (x = 0; x < hw; x++)
                dst[x] = av_clip_uint8(input[(n - hh + y) * n + x].re * scale);
        }
        for (y = 0; y < hh; y++) {
            uint8_t *dst = out->data[plane] + y * out->linesize[plane];
            for (x = 0; x < hw; x++)
                dst[x] = av_clip_uint8(input[(n - hh + y) * n + n - hw + x].re * scale);
        }
    } else {
        for (y = 0; y < hh; y++) {
            uint16_t *dst = (uint16_t *)(out->data[plane] + (y + hh) * out->linesize[plane] + hw * 2);
            for (x = 0; x < hw; x++)
                dst[x] = av_clip(input[y * n + x].re * scale, 0, max);
        }
        for (y = 0; y < hh; y++) {
            uint16_t *dst = (uint16_t *)(out->data[plane] + (y + hh) * out->linesize[plane]);
            for (x = 0; x < hw; x++)
                dst[x] = av_clip(input[y * n + n - hw + x].re * scale, 0, max);
        }
        for (y = 0; y < hh; y++) {
            uint16_t *dst = (uint16_t *)(out->data[plane] + y * out->linesize[plane] + hw * 2);
            for (x = 0; x < hw; x++)
                dst[x] = av_clip(input[(n - hh + y) * n + x].re * scale, 0, max);
        }
        for (y = 0; y < hh; y++) {
            uint16_t *dst = (uint16_t *)(out->data[plane] + y * out->linesize[plane]);
            for (x = 0; x < hw; x++)
                dst[x] = av_clip(input[(n - hh + y) * n + n - hw + x].re * scale, 0, max);
        }
    }
}