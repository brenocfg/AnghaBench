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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int depth; int /*<<< orphan*/  (* export_row ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const,float const,int const) ;TYPE_1__* planes; } ;
struct TYPE_4__ {int planewidth; int planeheight; int b; int o; int nox; int noy; int data_linesize; int /*<<< orphan*/  ifft; int /*<<< orphan*/ * vdata; int /*<<< orphan*/ * hdata; } ;
typedef  TYPE_1__ PlaneContext ;
typedef  TYPE_2__ FFTdnoizContext ;
typedef  int /*<<< orphan*/  FFTComplex ;

/* Variables and functions */
 int const FFMIN (int const,int const) ; 
 int /*<<< orphan*/  av_fft_calc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_fft_permute (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,float*,int const) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const,float const,int const) ; 

__attribute__((used)) static void export_plane(FFTdnoizContext *s,
                         uint8_t *dstp, int dst_linesize,
                         float *buffer, int buffer_linesize, int plane)
{
    PlaneContext *p = &s->planes[plane];
    const int depth = s->depth;
    const int bpp = (depth + 7) / 8;
    const int width = p->planewidth;
    const int height = p->planeheight;
    const int block = p->b;
    const int overlap = p->o;
    const int hoverlap = overlap / 2;
    const int size = block - overlap;
    const int nox = p->nox;
    const int noy = p->noy;
    const int data_linesize = p->data_linesize / sizeof(FFTComplex);
    const float scale = 1.f / (block * block);
    FFTComplex *hdata = p->hdata;
    FFTComplex *vdata = p->vdata;
    int x, y, i, j;

    buffer_linesize /= sizeof(float);
    for (y = 0; y < noy; y++) {
        for (x = 0; x < nox; x++) {
            const int woff = x == 0 ? 0 : hoverlap;
            const int hoff = y == 0 ? 0 : hoverlap;
            const int rw = x == 0 ? block : FFMIN(size, width  - x * size - woff);
            const int rh = y == 0 ? block : FFMIN(size, height - y * size - hoff);
            float *bsrc = buffer + buffer_linesize * y * block + x * block * 2;
            uint8_t *dst = dstp + dst_linesize * (y * size + hoff) + (x * size + woff) * bpp;
            FFTComplex *hdst, *ddst = vdata;

            hdst = hdata;
            for (i = 0; i < block; i++) {
                memcpy(ddst, bsrc, block * sizeof(FFTComplex));
                av_fft_permute(p->ifft, ddst);
                av_fft_calc(p->ifft, ddst);
                for (j = 0; j < block; j++) {
                    hdst[j * data_linesize + i] = ddst[j];
                }

                ddst += data_linesize;
                bsrc += buffer_linesize;
            }

            hdst = hdata + hoff * data_linesize;
            for (i = 0; i < rh; i++) {
                av_fft_permute(p->ifft, hdst);
                av_fft_calc(p->ifft, hdst);
                s->export_row(hdst + woff, dst, rw, scale, depth);

                hdst += data_linesize;
                dst += dst_linesize;
            }
        }
    }
}