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
struct TYPE_3__ {scalar_t__ calculations_use_input_precision; } ;
typedef  TYPE_1__ png_modifier ;

/* Variables and functions */

__attribute__((used)) static int output_quantization_factor(const png_modifier *pm, int in_depth,
   int out_depth)
{
   if (out_depth == 16 && in_depth != 16 &&
      pm->calculations_use_input_precision)
      return 257;
   else
      return 1;
}