#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resampler_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* process ) (void*,struct resampler_data*) ;} ;
typedef  TYPE_1__ rarch_CC_resampler_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (void*,struct resampler_data*) ; 

__attribute__((used)) static void resampler_CC_process(void *re_, struct resampler_data *data)
{
   rarch_CC_resampler_t *re = (rarch_CC_resampler_t*)re_;
   if (re)
      re->process(re_, data);
}