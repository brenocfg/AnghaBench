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
struct TYPE_2__ {int /*<<< orphan*/  features; } ;
typedef  int /*<<< orphan*/  FEATURES_T ;
typedef  scalar_t__ EGLint ;

/* Variables and functions */
 scalar_t__ FEATURES_UNPACK_ALPHA (int /*<<< orphan*/ ) ; 
 scalar_t__ FEATURES_UNPACK_BLUE (int /*<<< orphan*/ ) ; 
 scalar_t__ FEATURES_UNPACK_COLOR (int /*<<< orphan*/ ) ; 
 scalar_t__ FEATURES_UNPACK_DEPTH (int /*<<< orphan*/ ) ; 
 scalar_t__ FEATURES_UNPACK_GREEN (int /*<<< orphan*/ ) ; 
 scalar_t__ FEATURES_UNPACK_MASK (int /*<<< orphan*/ ) ; 
 scalar_t__ FEATURES_UNPACK_MULTI (int /*<<< orphan*/ ) ; 
 scalar_t__ FEATURES_UNPACK_RED (int /*<<< orphan*/ ) ; 
 scalar_t__ FEATURES_UNPACK_STENCIL (int /*<<< orphan*/ ) ; 
 TYPE_1__* formats ; 

__attribute__((used)) static bool less_than(int id0, int id1, bool use_red, bool use_green, bool use_blue, bool use_alpha)
{
   FEATURES_T features0 = formats[id0].features;
   FEATURES_T features1 = formats[id1].features;

   EGLint all0 = FEATURES_UNPACK_COLOR(features0);
   EGLint all1 = FEATURES_UNPACK_COLOR(features1);

   EGLint multi0 = FEATURES_UNPACK_MULTI(features0);
   EGLint multi1 = FEATURES_UNPACK_MULTI(features1);

   EGLint depth0 = FEATURES_UNPACK_DEPTH(features0);
   EGLint depth1 = FEATURES_UNPACK_DEPTH(features1);

   EGLint stencil0 = FEATURES_UNPACK_STENCIL(features0);
   EGLint stencil1 = FEATURES_UNPACK_STENCIL(features1);

   EGLint mask0 = FEATURES_UNPACK_MASK(features0);
   EGLint mask1 = FEATURES_UNPACK_MASK(features1);

   int used0 = 0;
   int used1 = 0;

   if (use_red) {
      used0 += FEATURES_UNPACK_RED(features0);
      used1 += FEATURES_UNPACK_RED(features1);
   }
   if (use_green) {
      used0 += FEATURES_UNPACK_GREEN(features0);
      used1 += FEATURES_UNPACK_GREEN(features1);
   }
   if (use_blue) {
      used0 += FEATURES_UNPACK_BLUE(features0);
      used1 += FEATURES_UNPACK_BLUE(features1);
   }
   if (use_alpha) {
      used0 += FEATURES_UNPACK_ALPHA(features0);
      used1 += FEATURES_UNPACK_ALPHA(features1);
   }

   return used0 > used1    ||    (used0 == used1 &&
      (all0 < all1         ||     (all0 == all1 &&
      (multi0 < multi1     ||   (multi0 == multi1 &&
      (depth0 < depth1     ||   (depth0 == depth1 &&
      (stencil0 < stencil1 || (stencil0 == stencil1 &&
      (mask0 < mask1))))))))));
}