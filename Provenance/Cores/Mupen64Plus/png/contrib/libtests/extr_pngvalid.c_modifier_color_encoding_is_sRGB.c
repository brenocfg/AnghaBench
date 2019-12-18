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
struct TYPE_5__ {scalar_t__ current_gamma; TYPE_1__* current_encoding; TYPE_1__* encodings; } ;
typedef  TYPE_2__ png_modifier ;
struct TYPE_4__ {scalar_t__ gamma; } ;

/* Variables and functions */

__attribute__((used)) static int
modifier_color_encoding_is_sRGB(const png_modifier *pm)
{
   return pm->current_encoding != 0 && pm->current_encoding == pm->encodings &&
      pm->current_encoding->gamma == pm->current_gamma;
}