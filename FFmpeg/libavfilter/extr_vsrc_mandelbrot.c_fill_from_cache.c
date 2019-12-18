#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {TYPE_2__* priv; } ;
struct TYPE_6__ {int cache_used; double start_x; int w; int cache_allocated; TYPE_1__* next_cache; TYPE_1__* point_cache; scalar_t__ morphamp; } ;
struct TYPE_5__ {double* p; int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ Point ;
typedef  TYPE_2__ MBContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int lrint (double) ; 

__attribute__((used)) static void fill_from_cache(AVFilterContext *ctx, uint32_t *color, int *in_cidx, int *out_cidx, double py, double scale){
    MBContext *s = ctx->priv;
    if(s->morphamp)
        return;
    for(; *in_cidx < s->cache_used; (*in_cidx)++){
        Point *p= &s->point_cache[*in_cidx];
        int x;
        if(p->p[1] > py)
            break;
        x= lrint((p->p[0] - s->start_x) / scale + s->w/2);
        if(x<0 || x >= s->w)
            continue;
        if(color) color[x] = p->val;
        if(out_cidx && *out_cidx < s->cache_allocated)
            s->next_cache[(*out_cidx)++]= *p;
    }
}