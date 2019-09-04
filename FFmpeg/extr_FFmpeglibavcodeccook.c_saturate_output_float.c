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
struct TYPE_4__ {int /*<<< orphan*/  (* vector_clipf ) (float*,scalar_t__,int /*<<< orphan*/ ,float,float) ;} ;
struct TYPE_5__ {scalar_t__ samples_per_channel; scalar_t__ mono_mdct_output; TYPE_1__ adsp; } ;
typedef  TYPE_2__ COOKContext ;

/* Variables and functions */
 int /*<<< orphan*/  FFALIGN (scalar_t__,int) ; 
 int /*<<< orphan*/  stub1 (float*,scalar_t__,int /*<<< orphan*/ ,float,float) ; 

__attribute__((used)) static void saturate_output_float(COOKContext *q, float *out)
{
    q->adsp.vector_clipf(out, q->mono_mdct_output + q->samples_per_channel,
                         FFALIGN(q->samples_per_channel, 8), -1.0f, 1.0f);
}