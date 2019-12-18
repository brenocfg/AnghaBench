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
typedef  TYPE_1__* png_const_structrp ;
typedef  int /*<<< orphan*/  png_const_charp ;
typedef  int /*<<< orphan*/  png_colorspacerp ;
struct TYPE_5__ {scalar_t__ user_chunk_malloc_max; } ;

/* Variables and functions */
 scalar_t__ PNG_SIZE_MAX ; 
 scalar_t__ PNG_USER_CHUNK_MALLOC_MAX ; 
 int /*<<< orphan*/  icc_check_length (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int png_icc_profile_error (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*) ; 

int /* PRIVATE */
png_icc_check_length(png_const_structrp png_ptr, png_colorspacerp colorspace,
    png_const_charp name, png_uint_32 profile_length)
{
   if (!icc_check_length(png_ptr, colorspace, name, profile_length))
      return 0;

   /* This needs to be here because the 'normal' check is in
    * png_decompress_chunk, yet this happens after the attempt to
    * png_malloc_base the required data.  We only need this on read; on write
    * the caller supplies the profile buffer so libpng doesn't allocate it.  See
    * the call to icc_check_length below (the write case).
    */
#  ifdef PNG_SET_USER_LIMITS_SUPPORTED
      else if (png_ptr->user_chunk_malloc_max > 0 &&
               png_ptr->user_chunk_malloc_max < profile_length)
         return png_icc_profile_error(png_ptr, colorspace, name, profile_length,
             "exceeds application limits");
#  elif PNG_USER_CHUNK_MALLOC_MAX > 0
      else if (PNG_USER_CHUNK_MALLOC_MAX < profile_length)
         return png_icc_profile_error(png_ptr, colorspace, name, profile_length,
             "exceeds libpng limits");
#  else /* !SET_USER_LIMITS */
      /* This will get compiled out on all 32-bit and better systems. */
      else if (PNG_SIZE_MAX < profile_length)
         return png_icc_profile_error(png_ptr, colorspace, name, profile_length,
             "exceeds system limits");
#  endif /* !SET_USER_LIMITS */

   return 1;
}