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
struct TYPE_3__ {int out_pix_fmt; } ;
typedef  TYPE_1__ rarch_softfilter_t ;
typedef  enum retro_pixel_format { ____Placeholder_retro_pixel_format } retro_pixel_format ;

/* Variables and functions */

enum retro_pixel_format rarch_softfilter_get_output_format(
      rarch_softfilter_t *filt)
{
   return filt->out_pix_fmt;
}