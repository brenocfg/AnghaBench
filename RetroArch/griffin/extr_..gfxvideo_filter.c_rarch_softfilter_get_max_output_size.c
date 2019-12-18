#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; } ;
typedef  TYPE_1__ rarch_softfilter_t ;

/* Variables and functions */
 int /*<<< orphan*/  rarch_softfilter_get_output_size (TYPE_1__*,unsigned int*,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rarch_softfilter_get_max_output_size(rarch_softfilter_t *filt,
      unsigned *width, unsigned *height)
{
   rarch_softfilter_get_output_size(filt, width, height,
         filt->max_width, filt->max_height);
}