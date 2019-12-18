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
struct sunxi_video {TYPE_1__* sunxi_disp; } ;
struct TYPE_2__ {float refresh_rate; } ;

/* Variables and functions */

__attribute__((used)) static float sunxi_get_refresh_rate (void *data)
{
   struct sunxi_video *_dispvars = (struct sunxi_video*)data;

   return _dispvars->sunxi_disp->refresh_rate;
}