#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  max_gamma_8; } ;
typedef  TYPE_1__ transform_display ;
typedef  int /*<<< orphan*/  png_structp ;
typedef  int /*<<< orphan*/  png_infop ;
struct TYPE_8__ {TYPE_3__* next; } ;
typedef  TYPE_2__ image_transform ;
struct TYPE_9__ {int /*<<< orphan*/  (* set ) (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_MAX_GAMMA_8 ; 
 int /*<<< orphan*/  png_set_scale_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
image_transform_png_set_scale_16_set(const image_transform *this,
    transform_display *that, png_structp pp, png_infop pi)
{
   png_set_scale_16(pp);
#  if PNG_LIBPNG_VER < 10700
      /* libpng will limit the gamma table size: */
      that->max_gamma_8 = PNG_MAX_GAMMA_8;
#  endif
   this->next->set(this->next, that, pp, pi);
}