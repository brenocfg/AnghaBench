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
typedef  void** png_const_bytep ;
typedef  TYPE_1__* png_colorp ;
typedef  scalar_t__* png_bytep ;
typedef  scalar_t__ png_byte ;
struct TYPE_3__ {void* blue; void* green; void* red; } ;

/* Variables and functions */

__attribute__((used)) static void
set_color(png_colorp color, png_bytep trans, unsigned int red,
   unsigned int green, unsigned int blue, unsigned int alpha,
   png_const_bytep gamma_table)
{
   color->red = gamma_table[red];
   color->green = gamma_table[green];
   color->blue = gamma_table[blue];
   *trans = (png_byte)alpha;
}