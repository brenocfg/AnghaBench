#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {int* buf; int buf_row_idx; int w; int buf_prev_row_idx; int h; int rule; int /*<<< orphan*/  generation; scalar_t__ stitch; } ;
typedef  TYPE_1__ CellAutoContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_dlog (TYPE_2__*,char*,int,char,char,char,int) ; 

__attribute__((used)) static void evolve(AVFilterContext *ctx)
{
    CellAutoContext *s = ctx->priv;
    int i, v, pos[3];
    uint8_t *row, *prev_row = s->buf + s->buf_row_idx * s->w;
    enum { NW, N, NE };

    s->buf_prev_row_idx = s->buf_row_idx;
    s->buf_row_idx      = s->buf_row_idx == s->h-1 ? 0 : s->buf_row_idx+1;
    row = s->buf + s->w * s->buf_row_idx;

    for (i = 0; i < s->w; i++) {
        if (s->stitch) {
            pos[NW] = i-1 < 0 ? s->w-1 : i-1;
            pos[N]  = i;
            pos[NE] = i+1 == s->w ? 0  : i+1;
            v = prev_row[pos[NW]]<<2 | prev_row[pos[N]]<<1 | prev_row[pos[NE]];
        } else {
            v = 0;
            v|= i-1 >= 0          ? prev_row[i-1]<<2 : 0;
            v|=                     prev_row[i  ]<<1    ;
            v|= i+1 < s->w ? prev_row[i+1]    : 0;
        }
        row[i] = !!(s->rule & (1<<v));
        ff_dlog(ctx, "i:%d context:%c%c%c -> cell:%d\n", i,
                v&4?'@':' ', v&2?'@':' ', v&1?'@':' ', row[i]);
    }

    s->generation++;
}