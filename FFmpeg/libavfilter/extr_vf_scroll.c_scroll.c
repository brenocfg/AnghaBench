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
struct TYPE_9__ {int width; int height; int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_8__ {int h_pos; int v_pos; int bytes; int nb_planes; int* planeheight; int* planewidth; int h_speed; int v_speed; TYPE_1__* desc; } ;
struct TYPE_7__ {int /*<<< orphan*/  log2_chroma_w; int /*<<< orphan*/  log2_chroma_h; } ;
typedef  TYPE_2__ ScrollContext ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 void* fmodf (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int const) ; 

__attribute__((used)) static void scroll(ScrollContext *s, AVFrame *in, AVFrame *out)
{
    int h_pos, v_pos;
    int pos_h[4], pos_v[4];

    s->h_pos = fmodf(s->h_pos, in->width);
    s->v_pos = fmodf(s->v_pos, in->height);

    h_pos = s->h_pos;
    v_pos = s->v_pos;

    if (h_pos < 0)
        h_pos += in->width;
    if (v_pos < 0)
        v_pos += in->height;

    pos_v[1] = pos_v[2] = AV_CEIL_RSHIFT(v_pos, s->desc->log2_chroma_h);
    pos_v[0] = pos_v[3] = v_pos;
    pos_h[1] = pos_h[2] = AV_CEIL_RSHIFT(h_pos, s->desc->log2_chroma_w) * s->bytes;
    pos_h[0] = pos_h[3] = h_pos * s->bytes;

    for (int p = 0; p < s->nb_planes; p++) {
        const uint8_t *src = in->data[p];
        uint8_t *dst = out->data[p];
        const int h = s->planeheight[p];
        const int w = s->planewidth[p] * s->bytes;

        for (int y = 0; y < h; y++) {
            int yy = (y + pos_v[p]) % h;
            const uint8_t *ssrc = src + yy * in->linesize[p];

            if (pos_h[p] < w)
                memcpy(dst, ssrc + pos_h[p], w - pos_h[p]);
            if (pos_h[p] > 0)
                memcpy(dst + w - pos_h[p], ssrc, pos_h[p]);

            dst += out->linesize[p];
        }
    }

    s->h_pos += s->h_speed * in->width;
    s->v_pos += s->v_speed * in->height;
}