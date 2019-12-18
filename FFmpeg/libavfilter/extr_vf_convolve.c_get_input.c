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
typedef  float uint8_t ;
typedef  float uint16_t ;
struct TYPE_9__ {float** data; int* linesize; } ;
struct TYPE_8__ {int depth; } ;
struct TYPE_7__ {float re; scalar_t__ im; } ;
typedef  TYPE_1__ FFTComplex ;
typedef  TYPE_2__ ConvolveContext ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */

__attribute__((used)) static void get_input(ConvolveContext *s, FFTComplex *fft_hdata,
                      AVFrame *in, int w, int h, int n, int plane, float scale)
{
    const int iw = (n - w) / 2, ih = (n - h) / 2;
    int y, x;

    if (s->depth == 8) {
        for (y = 0; y < h; y++) {
            const uint8_t *src = in->data[plane] + in->linesize[plane] * y;

            for (x = 0; x < w; x++) {
                fft_hdata[(y + ih) * n + iw + x].re = src[x] * scale;
                fft_hdata[(y + ih) * n + iw + x].im = 0;
            }

            for (x = 0; x < iw; x++) {
                fft_hdata[(y + ih) * n + x].re = fft_hdata[(y + ih) * n + iw].re;
                fft_hdata[(y + ih) * n + x].im = 0;
            }

            for (x = n - iw; x < n; x++) {
                fft_hdata[(y + ih) * n + x].re = fft_hdata[(y + ih) * n + n - iw - 1].re;
                fft_hdata[(y + ih) * n + x].im = 0;
            }
        }

        for (y = 0; y < ih; y++) {
            for (x = 0; x < n; x++) {
                fft_hdata[y * n + x].re = fft_hdata[ih * n + x].re;
                fft_hdata[y * n + x].im = 0;
            }
        }

        for (y = n - ih; y < n; y++) {
            for (x = 0; x < n; x++) {
                fft_hdata[y * n + x].re = fft_hdata[(n - ih - 1) * n + x].re;
                fft_hdata[y * n + x].im = 0;
            }
        }
    } else {
        for (y = 0; y < h; y++) {
            const uint16_t *src = (const uint16_t *)(in->data[plane] + in->linesize[plane] * y);

            for (x = 0; x < w; x++) {
                fft_hdata[(y + ih) * n + iw + x].re = src[x] * scale;
                fft_hdata[(y + ih) * n + iw + x].im = 0;
            }

            for (x = 0; x < iw; x++) {
                fft_hdata[(y + ih) * n + x].re = fft_hdata[(y + ih) * n + iw].re;
                fft_hdata[(y + ih) * n + x].im = 0;
            }

            for (x = n - iw; x < n; x++) {
                fft_hdata[(y + ih) * n + x].re = fft_hdata[(y + ih) * n + n - iw - 1].re;
                fft_hdata[(y + ih) * n + x].im = 0;
            }
        }

        for (y = 0; y < ih; y++) {
            for (x = 0; x < n; x++) {
                fft_hdata[y * n + x].re = fft_hdata[ih * n + x].re;
                fft_hdata[y * n + x].im = 0;
            }
        }

        for (y = n - ih; y < n; y++) {
            for (x = 0; x < n; x++) {
                fft_hdata[y * n + x].re = fft_hdata[(n - ih - 1) * n + x].re;
                fft_hdata[y * n + x].im = 0;
            }
        }
    }
}