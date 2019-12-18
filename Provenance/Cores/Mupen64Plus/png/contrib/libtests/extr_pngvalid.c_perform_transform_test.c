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
typedef  scalar_t__ png_uint_32 ;
struct TYPE_5__ {int /*<<< orphan*/  interlace_type; scalar_t__ repeat; int /*<<< orphan*/  test_tRNS; int /*<<< orphan*/  test_lbg; } ;
typedef  TYPE_1__ png_modifier ;
typedef  int /*<<< orphan*/  png_byte ;
typedef  int /*<<< orphan*/  image_transform ;

/* Variables and functions */
 int /*<<< orphan*/  FILEID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fail (TYPE_1__*) ; 
 scalar_t__ image_transform_add (int /*<<< orphan*/  const**,int,scalar_t__,char*,int,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ next_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t safecat (char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  transform_test (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char*) ; 

__attribute__((used)) static void
perform_transform_test(png_modifier *pm)
{
   png_byte colour_type = 0;
   png_byte bit_depth = 0;
   unsigned int palette_number = 0;

   while (next_format(&colour_type, &bit_depth, &palette_number, pm->test_lbg,
            pm->test_tRNS))
   {
      png_uint_32 counter = 0;
      size_t base_pos;
      char name[64];

      base_pos = safecat(name, sizeof name, 0, "transform:");

      for (;;)
      {
         size_t pos = base_pos;
         const image_transform *list = 0;

         /* 'max' is currently hardwired to '1'; this should be settable on the
          * command line.
          */
         counter = image_transform_add(&list, 1/*max*/, counter,
            name, sizeof name, &pos, colour_type, bit_depth);

         if (counter == 0)
            break;

         /* The command line can change this to checking interlaced images. */
         do
         {
            pm->repeat = 0;
            transform_test(pm, FILEID(colour_type, bit_depth, palette_number,
               pm->interlace_type, 0, 0, 0), list, name);

            if (fail(pm))
               return;
         }
         while (pm->repeat);
      }
   }
}