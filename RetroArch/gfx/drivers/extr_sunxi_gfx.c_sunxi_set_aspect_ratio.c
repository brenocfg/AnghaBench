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
struct sunxi_video {float aspect_ratio; int /*<<< orphan*/  src_pitch; int /*<<< orphan*/  src_height; int /*<<< orphan*/  src_width; } ;
struct TYPE_2__ {float value; } ;

/* Variables and functions */
 TYPE_1__* aspectratio_lut ; 
 int /*<<< orphan*/  sunxi_setup_scale (struct sunxi_video*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sunxi_set_aspect_ratio(void *data, unsigned aspect_ratio_idx)
{
   struct sunxi_video *_dispvars = (struct sunxi_video*)data;
   float              new_aspect = aspectratio_lut[aspect_ratio_idx].value;

   if (new_aspect != _dispvars->aspect_ratio)
   {
      /* Here we set the new aspect ratio. */
      _dispvars->aspect_ratio = new_aspect;
      sunxi_setup_scale(_dispvars, _dispvars->src_width, _dispvars->src_height, _dispvars->src_pitch);
   }
}