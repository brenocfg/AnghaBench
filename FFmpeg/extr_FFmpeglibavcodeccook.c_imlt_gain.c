#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__* now; } ;
typedef  TYPE_1__ cook_gains ;
struct TYPE_11__ {int /*<<< orphan*/  (* imdct_calc ) (TYPE_6__*,float*,float*) ;} ;
struct TYPE_10__ {float* mono_mdct_output; int samples_per_channel; int gain_size_factor; int /*<<< orphan*/  (* interpolate ) (TYPE_2__*,float*,scalar_t__,scalar_t__) ;int /*<<< orphan*/  (* imlt_window ) (TYPE_2__*,float*,TYPE_1__*,float*) ;TYPE_6__ mdct_ctx; } ;
typedef  TYPE_2__ COOKContext ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,float*,float*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,float*,TYPE_1__*,float*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,float*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void imlt_gain(COOKContext *q, float *inbuffer,
                      cook_gains *gains_ptr, float *previous_buffer)
{
    float *buffer0 = q->mono_mdct_output;
    float *buffer1 = q->mono_mdct_output + q->samples_per_channel;
    int i;

    /* Inverse modified discrete cosine transform */
    q->mdct_ctx.imdct_calc(&q->mdct_ctx, q->mono_mdct_output, inbuffer);

    q->imlt_window(q, buffer1, gains_ptr, previous_buffer);

    /* Apply gain profile */
    for (i = 0; i < 8; i++)
        if (gains_ptr->now[i] || gains_ptr->now[i + 1])
            q->interpolate(q, &buffer1[q->gain_size_factor * i],
                           gains_ptr->now[i], gains_ptr->now[i + 1]);

    /* Save away the current to be previous block. */
    memcpy(previous_buffer, buffer0,
           q->samples_per_channel * sizeof(*previous_buffer));
}