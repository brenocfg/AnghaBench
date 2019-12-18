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
struct TYPE_4__ {int /*<<< orphan*/  bluey; int /*<<< orphan*/  bluex; int /*<<< orphan*/  greeny; int /*<<< orphan*/  greenx; int /*<<< orphan*/  redy; int /*<<< orphan*/  redx; int /*<<< orphan*/  whitey; int /*<<< orphan*/  whitex; } ;
typedef  TYPE_1__ png_xy ;

/* Variables and functions */
 scalar_t__ PNG_OUT_OF_RANGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
png_colorspace_endpoints_match(const png_xy *xy1, const png_xy *xy2, int delta)
{
   /* Allow an error of +/-0.01 (absolute value) on each chromaticity */
   if (PNG_OUT_OF_RANGE(xy1->whitex, xy2->whitex,delta) ||
       PNG_OUT_OF_RANGE(xy1->whitey, xy2->whitey,delta) ||
       PNG_OUT_OF_RANGE(xy1->redx,   xy2->redx,  delta) ||
       PNG_OUT_OF_RANGE(xy1->redy,   xy2->redy,  delta) ||
       PNG_OUT_OF_RANGE(xy1->greenx, xy2->greenx,delta) ||
       PNG_OUT_OF_RANGE(xy1->greeny, xy2->greeny,delta) ||
       PNG_OUT_OF_RANGE(xy1->bluex,  xy2->bluex, delta) ||
       PNG_OUT_OF_RANGE(xy1->bluey,  xy2->bluey, delta))
      return 0;
   return 1;
}