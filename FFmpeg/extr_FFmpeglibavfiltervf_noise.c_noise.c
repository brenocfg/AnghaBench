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
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  int8_t ;
struct TYPE_5__ {int flags; int* rand_shift; int /*<<< orphan*/ *** prev_shift; int /*<<< orphan*/ * noise; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* line_noise ) (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int) ;int /*<<< orphan*/  (* line_noise_avg ) (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const**) ;TYPE_2__* param; } ;
typedef  TYPE_1__ NoiseContext ;
typedef  TYPE_2__ FilterParams ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int MAX_RES ; 
 int const NOISE_AVERAGED ; 
 int /*<<< orphan*/  av_image_copy_plane (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void noise(uint8_t *dst, const uint8_t *src,
                  int dst_linesize, int src_linesize,
                  int width, int start, int end, NoiseContext *n, int comp)
{
    FilterParams *p = &n->param[comp];
    int8_t *noise = p->noise;
    const int flags = p->flags;
    int y;

    if (!noise) {
        if (dst != src)
            av_image_copy_plane(dst, dst_linesize, src, src_linesize, width, end - start);
        return;
    }

    for (y = start; y < end; y++) {
        const int ix = y & (MAX_RES - 1);
        int x;
        for (x=0; x < width; x+= MAX_RES) {
            int w = FFMIN(width - x, MAX_RES);
            int shift = p->rand_shift[ix];

            if (flags & NOISE_AVERAGED) {
                n->line_noise_avg(dst + x, src + x, w, (const int8_t**)p->prev_shift[ix]);
                p->prev_shift[ix][shift & 3] = noise + shift;
            } else {
                n->line_noise(dst + x, src + x, noise, w, shift);
            }
        }
        dst += dst_linesize;
        src += src_linesize;
    }
}