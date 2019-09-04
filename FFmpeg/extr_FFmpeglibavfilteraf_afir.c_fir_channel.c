#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* priv; } ;
struct TYPE_9__ {int nb_samples; } ;
struct TYPE_8__ {scalar_t__ min_part_size; } ;
typedef  TYPE_1__ AudioFIRContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  fir_quantum (TYPE_3__*,TYPE_2__*,int,int) ; 

__attribute__((used)) static int fir_channel(AVFilterContext *ctx, AVFrame *out, int ch)
{
    AudioFIRContext *s = ctx->priv;

    for (int offset = 0; offset < out->nb_samples; offset += s->min_part_size) {
        fir_quantum(ctx, out, ch, offset);
    }

    return 0;
}