#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  test; } ;
struct TYPE_4__ {TYPE_3__ this; } ;
typedef  TYPE_1__ png_modifier ;
typedef  int /*<<< orphan*/  png_byte ;

/* Variables and functions */
 int FILE_NAME_SIZE ; 
 int INTERLACE_LAST ; 
 int PNG_INTERLACE_NONE ; 
 int /*<<< orphan*/  do_own_interlace ; 
 int /*<<< orphan*/  make_transform_image (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,char*) ; 
 scalar_t__ next_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*,int,int) ; 
 int /*<<< orphan*/  safecat (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  standard_name (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
make_transform_images(png_modifier *pm)
{
   png_byte colour_type = 0;
   png_byte bit_depth = 0;
   unsigned int palette_number = 0;

   /* This is in case of errors. */
   safecat(pm->this.test, sizeof pm->this.test, 0, "make standard images");

   /* Use next_format to enumerate all the combinations we test, including
    * generating multiple low bit depth palette images. Non-A images (palette
    * and direct) are created with and without tRNS chunks.
    */
   while (next_format(&colour_type, &bit_depth, &palette_number, 1, 1))
   {
      int interlace_type;

      for (interlace_type = PNG_INTERLACE_NONE;
           interlace_type < INTERLACE_LAST; ++interlace_type)
      {
         char name[FILE_NAME_SIZE];

         standard_name(name, sizeof name, 0, colour_type, bit_depth,
            palette_number, interlace_type, 0, 0, do_own_interlace);
         make_transform_image(&pm->this, colour_type, bit_depth, palette_number,
            interlace_type, name);
      }
   }
}