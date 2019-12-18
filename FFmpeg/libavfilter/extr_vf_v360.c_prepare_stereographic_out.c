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
struct TYPE_4__ {int /*<<< orphan*/  v_fov; void** flat_range; int /*<<< orphan*/  h_fov; } ;
typedef  TYPE_1__ V360Context ;
struct TYPE_5__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 float FFMIN (int /*<<< orphan*/ ,float) ; 
 float M_PI ; 
 void* tanf (float) ; 

__attribute__((used)) static int prepare_stereographic_out(AVFilterContext *ctx)
{
    V360Context *s = ctx->priv;

    s->flat_range[0] = tanf(FFMIN(s->h_fov, 359.f) * M_PI / 720.f);
    s->flat_range[1] = tanf(FFMIN(s->v_fov, 359.f) * M_PI / 720.f);

    return 0;
}