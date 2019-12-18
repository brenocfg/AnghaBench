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
typedef  int png_uint_32 ;
struct TYPE_4__ {int /*<<< orphan*/  use_update_info; int /*<<< orphan*/  this; } ;
typedef  TYPE_1__ png_modifier ;
typedef  int png_byte ;

/* Variables and functions */
 int /*<<< orphan*/  DEPTH (int) ; 
 int /*<<< orphan*/  FILEID (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  PNG_INTERLACE_ADAM7 ; 
 int /*<<< orphan*/  PNG_INTERLACE_NONE ; 
 scalar_t__ fail (TYPE_1__* const) ; 
 int /*<<< orphan*/  standard_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
test_size(png_modifier* const pm, png_byte const colour_type,
    int bdlo, int const bdhi)
{
   /* Run the tests on each combination.
    *
    * NOTE: on my 32 bit x86 each of the following blocks takes
    * a total of 3.5 seconds if done across every combo of bit depth
    * width and height.  This is a waste of time in practice, hence the
    * hinc and winc stuff:
    */
   static const png_byte hinc[] = {1, 3, 11, 1, 5};
   static const png_byte winc[] = {1, 9, 5, 7, 1};
   const int save_bdlo = bdlo;

   for (; bdlo <= bdhi; ++bdlo)
   {
      png_uint_32 h, w;

      for (h=1; h<=16; h+=hinc[bdlo]) for (w=1; w<=16; w+=winc[bdlo])
      {
         /* First test all the 'size' images against the sequential
          * reader using libpng to deinterlace (where required.)  This
          * validates the write side of libpng.  There are four possibilities
          * to validate.
          */
         standard_test(&pm->this, FILEID(colour_type, DEPTH(bdlo), 0/*palette*/,
            PNG_INTERLACE_NONE, w, h, 0), 0/*do_interlace*/,
            pm->use_update_info);

         if (fail(pm))
            return 0;

         standard_test(&pm->this, FILEID(colour_type, DEPTH(bdlo), 0/*palette*/,
            PNG_INTERLACE_NONE, w, h, 1), 0/*do_interlace*/,
            pm->use_update_info);

         if (fail(pm))
            return 0;

         /* Now validate the interlaced read side - do_interlace true,
          * in the progressive case this does actually make a difference
          * to the code used in the non-interlaced case too.
          */
         standard_test(&pm->this, FILEID(colour_type, DEPTH(bdlo), 0/*palette*/,
            PNG_INTERLACE_NONE, w, h, 0), 1/*do_interlace*/,
            pm->use_update_info);

         if (fail(pm))
            return 0;

#     if CAN_WRITE_INTERLACE
         /* Validate the pngvalid code itself: */
         standard_test(&pm->this, FILEID(colour_type, DEPTH(bdlo), 0/*palette*/,
            PNG_INTERLACE_ADAM7, w, h, 1), 1/*do_interlace*/,
            pm->use_update_info);

         if (fail(pm))
            return 0;
#     endif
      }
   }

   /* Now do the tests of libpng interlace handling, after we have made sure
    * that the pngvalid version works:
    */
   for (bdlo = save_bdlo; bdlo <= bdhi; ++bdlo)
   {
      png_uint_32 h, w;

      for (h=1; h<=16; h+=hinc[bdlo]) for (w=1; w<=16; w+=winc[bdlo])
      {
#     ifdef PNG_READ_INTERLACING_SUPPORTED
         /* Test with pngvalid generated interlaced images first; we have
          * already verify these are ok (unless pngvalid has self-consistent
          * read/write errors, which is unlikely), so this detects errors in the
          * read side first:
          */
#     if CAN_WRITE_INTERLACE
         standard_test(&pm->this, FILEID(colour_type, DEPTH(bdlo), 0/*palette*/,
            PNG_INTERLACE_ADAM7, w, h, 1), 0/*do_interlace*/,
            pm->use_update_info);

         if (fail(pm))
            return 0;
#     endif
#     endif /* READ_INTERLACING */

#     ifdef PNG_WRITE_INTERLACING_SUPPORTED
         /* Test the libpng write side against the pngvalid read side: */
         standard_test(&pm->this, FILEID(colour_type, DEPTH(bdlo), 0/*palette*/,
            PNG_INTERLACE_ADAM7, w, h, 0), 1/*do_interlace*/,
            pm->use_update_info);

         if (fail(pm))
            return 0;
#     endif

#     ifdef PNG_READ_INTERLACING_SUPPORTED
#     ifdef PNG_WRITE_INTERLACING_SUPPORTED
         /* Test both together: */
         standard_test(&pm->this, FILEID(colour_type, DEPTH(bdlo), 0/*palette*/,
            PNG_INTERLACE_ADAM7, w, h, 0), 0/*do_interlace*/,
            pm->use_update_info);

         if (fail(pm))
            return 0;
#     endif
#     endif /* READ_INTERLACING */
      }
   }

   return 1; /* keep going */
}