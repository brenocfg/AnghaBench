#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  main_buffer; } ;
typedef  TYPE_1__ rarch_sinc_resampler_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memalign_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void resampler_sinc_free(void *data)
{
   rarch_sinc_resampler_t *resamp = (rarch_sinc_resampler_t*)data;
   if (resamp)
      memalign_free(resamp->main_buffer);
   free(resamp);
}