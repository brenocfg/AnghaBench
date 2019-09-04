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
struct TYPE_9__ {TYPE_2__** inputs; TYPE_1__* priv; } ;
struct TYPE_8__ {int /*<<< orphan*/  format; } ;
struct TYPE_7__ {int channels; int orientation; } ;
typedef  TYPE_1__ SpectrumSynthContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
#define  AV_PIX_FMT_GRAY16 134 
#define  AV_PIX_FMT_GRAY8 133 
#define  AV_PIX_FMT_YUV444P 132 
#define  AV_PIX_FMT_YUV444P16 131 
#define  AV_PIX_FMT_YUVJ444P 130 
#define  HORIZONTAL 129 
#define  VERTICAL 128 
 int /*<<< orphan*/  read16_fft_bin (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  read8_fft_bin (TYPE_1__*,int,int,int,int) ; 

__attribute__((used)) static void read_fft_data(AVFilterContext *ctx, int x, int h, int ch)
{
    SpectrumSynthContext *s = ctx->priv;
    AVFilterLink *inlink = ctx->inputs[0];
    int start = h * (s->channels - ch) - 1;
    int end = h * (s->channels - ch - 1);
    int y, f;

    switch (s->orientation) {
    case VERTICAL:
        switch (inlink->format) {
        case AV_PIX_FMT_YUV444P16:
        case AV_PIX_FMT_GRAY16:
            for (y = start, f = 0; y >= end; y--, f++) {
                read16_fft_bin(s, x, y, f, ch);
            }
            break;
        case AV_PIX_FMT_YUVJ444P:
        case AV_PIX_FMT_YUV444P:
        case AV_PIX_FMT_GRAY8:
            for (y = start, f = 0; y >= end; y--, f++) {
                read8_fft_bin(s, x, y, f, ch);
            }
            break;
        }
        break;
    case HORIZONTAL:
        switch (inlink->format) {
        case AV_PIX_FMT_YUV444P16:
        case AV_PIX_FMT_GRAY16:
            for (y = end, f = 0; y <= start; y++, f++) {
                read16_fft_bin(s, y, x, f, ch);
            }
            break;
        case AV_PIX_FMT_YUVJ444P:
        case AV_PIX_FMT_YUV444P:
        case AV_PIX_FMT_GRAY8:
            for (y = end, f = 0; y <= start; y++, f++) {
                read8_fft_bin(s, y, x, f, ch);
            }
            break;
        }
        break;
    }
}