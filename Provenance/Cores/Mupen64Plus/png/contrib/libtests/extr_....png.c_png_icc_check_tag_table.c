#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ png_uint_32 ;
typedef  int /*<<< orphan*/  png_const_structrp ;
typedef  int /*<<< orphan*/  png_const_charp ;
typedef  scalar_t__ png_const_bytep ;
typedef  int /*<<< orphan*/ * png_colorspacerp ;

/* Variables and functions */
 scalar_t__ png_get_uint_32 (scalar_t__) ; 
 int png_icc_profile_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,char*) ; 

int /* PRIVATE */
png_icc_check_tag_table(png_const_structrp png_ptr, png_colorspacerp colorspace,
    png_const_charp name, png_uint_32 profile_length,
    png_const_bytep profile /* header plus whole tag table */)
{
   png_uint_32 tag_count = png_get_uint_32(profile+128);
   png_uint_32 itag;
   png_const_bytep tag = profile+132; /* The first tag */

   /* First scan all the tags in the table and add bits to the icc_info value
    * (temporarily in 'tags').
    */
   for (itag=0; itag < tag_count; ++itag, tag += 12)
   {
      png_uint_32 tag_id = png_get_uint_32(tag+0);
      png_uint_32 tag_start = png_get_uint_32(tag+4); /* must be aligned */
      png_uint_32 tag_length = png_get_uint_32(tag+8);/* not padded */

      /* The ICC specification does not exclude zero length tags, therefore the
       * start might actually be anywhere if there is no data, but this would be
       * a clear abuse of the intent of the standard so the start is checked for
       * being in range.  All defined tag types have an 8 byte header - a 4 byte
       * type signature then 0.
       */
      if ((tag_start & 3) != 0)
      {
         /* CNHP730S.icc shipped with Microsoft Windows 64 violates this, it is
          * only a warning here because libpng does not care about the
          * alignment.
          */
         (void)png_icc_profile_error(png_ptr, NULL, name, tag_id,
             "ICC profile tag start not a multiple of 4");
      }

      /* This is a hard error; potentially it can cause read outside the
       * profile.
       */
      if (tag_start > profile_length || tag_length > profile_length - tag_start)
         return png_icc_profile_error(png_ptr, colorspace, name, tag_id,
             "ICC profile tag outside profile");
   }

   return 1; /* success, maybe with warnings */
}