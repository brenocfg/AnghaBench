#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int sixteenbit_done; int colored_done; int alpha_done; unsigned char* palette; int maxnumcolors; int greybits; int greybits_done; scalar_t__ numcolors_done; int /*<<< orphan*/  tree; scalar_t__ numcolors; scalar_t__ alpha; scalar_t__ key; scalar_t__ colored; scalar_t__ sixteenbit; } ;
struct TYPE_8__ {int bitdepth; } ;
typedef  TYPE_1__ LodePNGColorMode ;
typedef  TYPE_2__ ColorProfile ;

/* Variables and functions */
 int /*<<< orphan*/  color_tree_init (int /*<<< orphan*/ *) ; 
 scalar_t__ lodepng_can_have_alpha (TYPE_1__ const*) ; 
 int lodepng_get_bpp (TYPE_1__ const*) ; 
 scalar_t__ lodepng_is_greyscale_type (TYPE_1__ const*) ; 
 scalar_t__ lodepng_malloc (int) ; 

__attribute__((used)) static void color_profile_init(ColorProfile* profile, const LodePNGColorMode* mode)
{
  profile->sixteenbit = 0;
  profile->sixteenbit_done = mode->bitdepth == 16 ? 0 : 1;

  profile->colored = 0;
  profile->colored_done = lodepng_is_greyscale_type(mode) ? 1 : 0;

  profile->key = 0;
  profile->alpha = 0;
  profile->alpha_done = lodepng_can_have_alpha(mode) ? 0 : 1;

  profile->numcolors = 0;
  color_tree_init(&profile->tree);
  profile->palette = (unsigned char*)lodepng_malloc(1024);
  profile->maxnumcolors = 257;
  if(lodepng_get_bpp(mode) <= 8)
  {
    int bpp = lodepng_get_bpp(mode);
    profile->maxnumcolors = bpp == 1 ? 2 : (bpp == 2 ? 4 : (bpp == 4 ? 16 : 256));
  }
  profile->numcolors_done = 0;

  profile->greybits = 1;
  profile->greybits_done = lodepng_get_bpp(mode) == 1 ? 1 : 0;
}