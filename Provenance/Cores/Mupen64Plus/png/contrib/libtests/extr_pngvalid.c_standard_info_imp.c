#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int use_update_info; } ;
typedef  TYPE_1__ standard_display ;
typedef  int /*<<< orphan*/  png_structp ;
typedef  int /*<<< orphan*/  png_infop ;

/* Variables and functions */
 int /*<<< orphan*/  png_read_update_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_start_read_image (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  standard_info_part1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  standard_info_part2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
standard_info_imp(standard_display *dp, png_structp pp, png_infop pi,
    int nImages)
{
   /* Note that the validation routine has the side effect of turning on
    * interlace handling in the subsequent code.
    */
   standard_info_part1(dp, pp, pi);

   /* And the info callback has to call this (or png_read_update_info - see
    * below in the png_modifier code for that variant.
    */
   if (dp->use_update_info)
   {
      /* For debugging the effect of multiple calls: */
      int i = dp->use_update_info;
      while (i-- > 0)
         png_read_update_info(pp, pi);
   }

   else
      png_start_read_image(pp);

   /* Validate the height, width and rowbytes plus ensure that sufficient buffer
    * exists for decoding the image.
    */
   standard_info_part2(dp, pp, pi, nImages);
}