#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int is_transparent; scalar_t__ has_tRNS; } ;
struct TYPE_9__ {TYPE_1__ this; } ;
typedef  TYPE_2__ transform_display ;
typedef  int /*<<< orphan*/  png_structp ;
typedef  int /*<<< orphan*/  png_infop ;
struct TYPE_10__ {TYPE_4__* next; } ;
typedef  TYPE_3__ image_transform ;
struct TYPE_11__ {int /*<<< orphan*/  (* set ) (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  png_set_expand_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
image_transform_png_set_expand_16_set(const image_transform *this,
    transform_display *that, png_structp pp, png_infop pi)
{
   png_set_expand_16(pp);

   /* NOTE: prior to 1.7 libpng does SET_EXPAND as well, so tRNS is expanded. */
#  if PNG_LIBPNG_VER < 10700
      if (that->this.has_tRNS)
         that->this.is_transparent = 1;
#  endif

   this->next->set(this->next, that, pp, pi);
}