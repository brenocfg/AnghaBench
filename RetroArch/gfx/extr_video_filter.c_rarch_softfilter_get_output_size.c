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
struct TYPE_5__ {int /*<<< orphan*/  impl_data; TYPE_1__* impl; } ;
typedef  TYPE_2__ rarch_softfilter_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* query_output_size ) (int /*<<< orphan*/ ,unsigned int*,unsigned int*,unsigned int,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int*,unsigned int*,unsigned int,unsigned int) ; 

void rarch_softfilter_get_output_size(rarch_softfilter_t *filt,
      unsigned *out_width, unsigned *out_height,
      unsigned width, unsigned height)
{
   if (filt && filt->impl && filt->impl->query_output_size)
      filt->impl->query_output_size(filt->impl_data, out_width,
            out_height, width, height);
}