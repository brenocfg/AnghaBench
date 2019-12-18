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
struct TYPE_8__ {TYPE_1__* priv; } ;
struct TYPE_7__ {TYPE_3__* src; } ;
struct TYPE_6__ {int kernel_size; void* tmp; void* offset; void* coeffs; void* delay; int /*<<< orphan*/  order; } ;
typedef  TYPE_1__ AudioNLMSContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFALIGN (int /*<<< orphan*/ ,int) ; 
 void* ff_get_audio_buffer (TYPE_2__*,int) ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    AudioNLMSContext *s = ctx->priv;

    s->kernel_size = FFALIGN(s->order, 16);

    if (!s->offset)
        s->offset = ff_get_audio_buffer(outlink, 1);
    if (!s->delay)
        s->delay = ff_get_audio_buffer(outlink, 2 * s->kernel_size);
    if (!s->coeffs)
        s->coeffs = ff_get_audio_buffer(outlink, 2 * s->kernel_size);
    if (!s->tmp)
        s->tmp = ff_get_audio_buffer(outlink, s->kernel_size);
    if (!s->delay || !s->coeffs || !s->offset || !s->tmp)
        return AVERROR(ENOMEM);

    return 0;
}