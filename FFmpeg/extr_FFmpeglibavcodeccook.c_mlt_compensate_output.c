#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cook_gains ;
struct TYPE_5__ {int /*<<< orphan*/  (* saturate_output ) (TYPE_1__*,float*) ;} ;
typedef  TYPE_1__ COOKContext ;

/* Variables and functions */
 int /*<<< orphan*/  imlt_gain (TYPE_1__*,float*,int /*<<< orphan*/ *,float*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,float*) ; 

__attribute__((used)) static inline void mlt_compensate_output(COOKContext *q, float *decode_buffer,
                                         cook_gains *gains_ptr, float *previous_buffer,
                                         float *out)
{
    imlt_gain(q, decode_buffer, gains_ptr, previous_buffer);
    if (out)
        q->saturate_output(q, out);
}