#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_8__ {TYPE_1__* priv; } ;
struct TYPE_7__ {int* linesize; scalar_t__* data; } ;
struct TYPE_6__ {scalar_t__ m; } ;
typedef  TYPE_1__ CiescopeContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  rgb_to_xy (double,double,double,double*,double*,double*,double const**) ; 

__attribute__((used)) static void filter_rgb48(AVFilterContext *ctx, AVFrame *in, double *cx, double *cy, int x, int y)
{
    CiescopeContext *s = ctx->priv;
    const uint16_t* src = (const uint16_t*)(in->data[0] + in->linesize[0] * y + x * 6);
    double r = src[0] / 65535.;
    double g = src[1] / 65535.;
    double b = src[2] / 65535.;
    double cz;

    rgb_to_xy(r, g, b, cx, cy, &cz, (const double (*)[3])s->m);
}