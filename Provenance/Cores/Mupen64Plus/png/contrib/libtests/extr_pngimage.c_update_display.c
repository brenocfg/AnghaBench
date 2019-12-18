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
struct display {int chunks; int bit_depth; int color_type; int active_transforms; int ignored_transforms; int /*<<< orphan*/  filter_method; int /*<<< orphan*/  compression_method; int /*<<< orphan*/  interlace_method; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/ * original_rows; int /*<<< orphan*/  original_rowbytes; int /*<<< orphan*/ * read_ip; int /*<<< orphan*/ * original_ip; int /*<<< orphan*/ * read_pp; int /*<<< orphan*/ * original_pp; int /*<<< orphan*/  original_file; } ;
typedef  int png_uint_32 ;
typedef  int /*<<< orphan*/ * png_structp ;
typedef  int /*<<< orphan*/ * png_infop ;
struct TYPE_2__ {int transform; int valid_chunks; int color_mask_required; int color_mask_absent; int bit_depths; int when; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBPNG_BUG ; 
 int PNG_INFO_IDAT ; 
 int TRANSFORM_R ; 
 unsigned int TTABLE_SIZE ; 
 int /*<<< orphan*/  display_log (struct display*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  png_get_IHDR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_get_rowbytes (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * png_get_rows (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int png_get_valid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  read_png (struct display*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* transform_info ; 

__attribute__((used)) static void
update_display(struct display *dp)
   /* called once after the first read to update all the info, original_pp and
    * original_ip must have been filled in.
    */
{
   png_structp pp;
   png_infop   ip;

   /* Now perform the initial read with a 0 tranform. */
   read_png(dp, &dp->original_file, "original read", 0/*no transform*/);

   /* Move the result to the 'original' fields */
   dp->original_pp = pp = dp->read_pp, dp->read_pp = NULL;
   dp->original_ip = ip = dp->read_ip, dp->read_ip = NULL;

   dp->original_rowbytes = png_get_rowbytes(pp, ip);
   if (dp->original_rowbytes == 0)
      display_log(dp, LIBPNG_BUG, "png_get_rowbytes returned 0");

   dp->chunks = png_get_valid(pp, ip, 0xffffffff);
   if ((dp->chunks & PNG_INFO_IDAT) == 0) /* set by png_read_png */
      display_log(dp, LIBPNG_BUG, "png_read_png did not set IDAT flag");

   dp->original_rows = png_get_rows(pp, ip);
   if (dp->original_rows == NULL)
      display_log(dp, LIBPNG_BUG, "png_read_png did not create row buffers");

   if (!png_get_IHDR(pp, ip,
      &dp->width, &dp->height, &dp->bit_depth, &dp->color_type,
      &dp->interlace_method, &dp->compression_method, &dp->filter_method))
      display_log(dp, LIBPNG_BUG, "png_get_IHDR failed");

   /* 'active' transforms are discovered based on the original image format;
    * running one active transform can activate others.  At present the code
    * does not attempt to determine the closure.
    */
   {
      png_uint_32 chunks = dp->chunks;
      int active = 0, inactive = 0;
      int ct = dp->color_type;
      int bd = dp->bit_depth;
      unsigned int i;

      for (i=0; i<TTABLE_SIZE; ++i) if (transform_info[i].name != NULL)
      {
         int transform = transform_info[i].transform;

         if ((transform_info[i].valid_chunks == 0 ||
               (transform_info[i].valid_chunks & chunks) != 0) &&
            (transform_info[i].color_mask_required & ct) ==
               transform_info[i].color_mask_required &&
            (transform_info[i].color_mask_absent & ct) == 0 &&
            (transform_info[i].bit_depths & bd) != 0 &&
            (transform_info[i].when & TRANSFORM_R) != 0)
            active |= transform;

         else if ((transform_info[i].when & TRANSFORM_R) != 0)
            inactive |= transform;
      }

      /* Some transforms appear multiple times in the table; the 'active' status
       * is the logical OR of these and the inactive status must be adjusted to
       * take this into account.
       */
      inactive &= ~active;

      dp->active_transforms = active;
      dp->ignored_transforms = inactive; /* excluding write-only transforms */
   }
}