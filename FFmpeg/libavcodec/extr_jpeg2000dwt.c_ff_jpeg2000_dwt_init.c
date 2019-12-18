#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ndeclevels; int type; int** linelen; int** mod; void* i_linebuf; void* f_linebuf; } ;
typedef  TYPE_1__ DWTContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMAX (int,int) ; 
#define  FF_DWT53 130 
#define  FF_DWT97 129 
#define  FF_DWT97_INT 128 
 void* av_malloc_array (int,int) ; 

int ff_jpeg2000_dwt_init(DWTContext *s, int border[2][2],
                         int decomp_levels, int type)
{
    int i, j, lev = decomp_levels, maxlen,
        b[2][2];

    s->ndeclevels = decomp_levels;
    s->type       = type;

    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++)
            b[i][j] = border[i][j];

    maxlen = FFMAX(b[0][1] - b[0][0],
                   b[1][1] - b[1][0]);
    while (--lev >= 0)
        for (i = 0; i < 2; i++) {
            s->linelen[lev][i] = b[i][1] - b[i][0];
            s->mod[lev][i]     = b[i][0] & 1;
            for (j = 0; j < 2; j++)
                b[i][j] = (b[i][j] + 1) >> 1;
        }
    switch (type) {
    case FF_DWT97:
        s->f_linebuf = av_malloc_array((maxlen + 12), sizeof(*s->f_linebuf));
        if (!s->f_linebuf)
            return AVERROR(ENOMEM);
        break;
     case FF_DWT97_INT:
        s->i_linebuf = av_malloc_array((maxlen + 12), sizeof(*s->i_linebuf));
        if (!s->i_linebuf)
            return AVERROR(ENOMEM);
        break;
    case FF_DWT53:
        s->i_linebuf = av_malloc_array((maxlen +  6), sizeof(*s->i_linebuf));
        if (!s->i_linebuf)
            return AVERROR(ENOMEM);
        break;
    default:
        return -1;
    }
    return 0;
}