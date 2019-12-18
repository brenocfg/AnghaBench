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
typedef  int png_byte ;
struct TYPE_4__ {struct TYPE_4__ const* next; } ;
typedef  TYPE_1__ image_transform ;

/* Variables and functions */
 int PNG_COLOR_TYPE_GRAY ; 
 int PNG_COLOR_TYPE_RGB ; 

__attribute__((used)) static int
image_transform_png_set_add_alpha_add(image_transform *this,
    const image_transform **that, png_byte colour_type, png_byte bit_depth)
{
   this->next = *that;
   *that = this;

   return bit_depth >= 8 && (colour_type == PNG_COLOR_TYPE_RGB ||
           colour_type == PNG_COLOR_TYPE_GRAY);
}