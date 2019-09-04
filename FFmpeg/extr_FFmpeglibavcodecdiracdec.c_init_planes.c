#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int width; int height; } ;
struct TYPE_11__ {int chroma_x_shift; int chroma_y_shift; int wavelet_depth; int pshift; TYPE_4__* plane; TYPE_1__ seq; } ;
struct TYPE_8__ {int width; int height; int stride; int buf; } ;
struct TYPE_10__ {int width; int height; int xblen; int yblen; int xbsep; int ybsep; int xoffset; int yoffset; TYPE_3__** band; TYPE_2__ idwt; } ;
struct TYPE_9__ {int pshift; int ibuf; int level; int stride; int width; int height; int orientation; struct TYPE_9__* parent; } ;
typedef  TYPE_3__ SubBand ;
typedef  TYPE_4__ Plane ;
typedef  TYPE_5__ DiracContext ;

/* Variables and functions */
 int CALC_PADDING (int,int) ; 
 int FFALIGN (int,int) ; 

__attribute__((used)) static void init_planes(DiracContext *s)
{
    int i, w, h, level, orientation;

    for (i = 0; i < 3; i++) {
        Plane *p = &s->plane[i];

        p->width       = s->seq.width  >> (i ? s->chroma_x_shift : 0);
        p->height      = s->seq.height >> (i ? s->chroma_y_shift : 0);
        p->idwt.width  = w = CALC_PADDING(p->width , s->wavelet_depth);
        p->idwt.height = h = CALC_PADDING(p->height, s->wavelet_depth);
        p->idwt.stride = FFALIGN(p->idwt.width, 8) << (1 + s->pshift);

        for (level = s->wavelet_depth-1; level >= 0; level--) {
            w = w>>1;
            h = h>>1;
            for (orientation = !!level; orientation < 4; orientation++) {
                SubBand *b = &p->band[level][orientation];

                b->pshift = s->pshift;
                b->ibuf   = p->idwt.buf;
                b->level  = level;
                b->stride = p->idwt.stride << (s->wavelet_depth - level);
                b->width  = w;
                b->height = h;
                b->orientation = orientation;

                if (orientation & 1)
                    b->ibuf += w << (1+b->pshift);
                if (orientation > 1)
                    b->ibuf += (b->stride>>1);

                if (level)
                    b->parent = &p->band[level-1][orientation];
            }
        }

        if (i > 0) {
            p->xblen = s->plane[0].xblen >> s->chroma_x_shift;
            p->yblen = s->plane[0].yblen >> s->chroma_y_shift;
            p->xbsep = s->plane[0].xbsep >> s->chroma_x_shift;
            p->ybsep = s->plane[0].ybsep >> s->chroma_y_shift;
        }

        p->xoffset = (p->xblen - p->xbsep)/2;
        p->yoffset = (p->yblen - p->ybsep)/2;
    }
}