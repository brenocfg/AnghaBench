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
typedef  int int32_t ;
struct TYPE_3__ {int** linelen; int ndeclevels; int* i_linebuf; int** mod; } ;
typedef  TYPE_1__ DWTContext ;

/* Variables and functions */
 int /*<<< orphan*/  sr_1d53 (int*,int,int) ; 

__attribute__((used)) static void dwt_decode53(DWTContext *s, int *t)
{
    int lev;
    int w     = s->linelen[s->ndeclevels - 1][0];
    int32_t *line = s->i_linebuf;
    line += 3;

    for (lev = 0; lev < s->ndeclevels; lev++) {
        int lh = s->linelen[lev][0],
            lv = s->linelen[lev][1],
            mh = s->mod[lev][0],
            mv = s->mod[lev][1],
            lp;
        int *l;

        // HOR_SD
        l = line + mh;
        for (lp = 0; lp < lv; lp++) {
            int i, j = 0;
            // copy with interleaving
            for (i = mh; i < lh; i += 2, j++)
                l[i] = t[w * lp + j];
            for (i = 1 - mh; i < lh; i += 2, j++)
                l[i] = t[w * lp + j];

            sr_1d53(line, mh, mh + lh);

            for (i = 0; i < lh; i++)
                t[w * lp + i] = l[i];
        }

        // VER_SD
        l = line + mv;
        for (lp = 0; lp < lh; lp++) {
            int i, j = 0;
            // copy with interleaving
            for (i = mv; i < lv; i += 2, j++)
                l[i] = t[w * j + lp];
            for (i = 1 - mv; i < lv; i += 2, j++)
                l[i] = t[w * j + lp];

            sr_1d53(line, mv, mv + lv);

            for (i = 0; i < lv; i++)
                t[w * i + lp] = l[i];
        }
    }
}