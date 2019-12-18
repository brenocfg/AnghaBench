#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ png_uint_32 ;
typedef  TYPE_2__* png_structrp ;
typedef  scalar_t__ png_size_t ;
typedef  scalar_t__ png_byte ;
typedef  scalar_t__ png_alloc_size_t ;
struct TYPE_9__ {int /*<<< orphan*/ * data; scalar_t__ location; scalar_t__ size; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {scalar_t__ user_chunk_malloc_max; TYPE_1__ unknown_chunk; scalar_t__ mode; int /*<<< orphan*/  chunk_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_CSTRING_FROM_CHUNK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PNG_SIZE_MAX ; 
 scalar_t__ PNG_USER_CHUNK_MALLOC_MAX ; 
 int /*<<< orphan*/  png_bytep ; 
 int /*<<< orphan*/  png_chunk_benign_error (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  png_crc_finish (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  png_crc_read (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  png_free (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_malloc_warn (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/ * png_voidcast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
png_cache_unknown_chunk(png_structrp png_ptr, png_uint_32 length)
{
   png_alloc_size_t limit = PNG_SIZE_MAX;

   if (png_ptr->unknown_chunk.data != NULL)
   {
      png_free(png_ptr, png_ptr->unknown_chunk.data);
      png_ptr->unknown_chunk.data = NULL;
   }

#  ifdef PNG_SET_USER_LIMITS_SUPPORTED
   if (png_ptr->user_chunk_malloc_max > 0 &&
       png_ptr->user_chunk_malloc_max < limit)
      limit = png_ptr->user_chunk_malloc_max;

#  elif PNG_USER_CHUNK_MALLOC_MAX > 0
   if (PNG_USER_CHUNK_MALLOC_MAX < limit)
      limit = PNG_USER_CHUNK_MALLOC_MAX;
#  endif

   if (length <= limit)
   {
      PNG_CSTRING_FROM_CHUNK(png_ptr->unknown_chunk.name, png_ptr->chunk_name);
      /* The following is safe because of the PNG_SIZE_MAX init above */
      png_ptr->unknown_chunk.size = (png_size_t)length/*SAFE*/;
      /* 'mode' is a flag array, only the bottom four bits matter here */
      png_ptr->unknown_chunk.location = (png_byte)png_ptr->mode/*SAFE*/;

      if (length == 0)
         png_ptr->unknown_chunk.data = NULL;

      else
      {
         /* Do a 'warn' here - it is handled below. */
         png_ptr->unknown_chunk.data = png_voidcast(png_bytep,
             png_malloc_warn(png_ptr, length));
      }
   }

   if (png_ptr->unknown_chunk.data == NULL && length > 0)
   {
      /* This is benign because we clean up correctly */
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "unknown chunk exceeds memory limits");
      return 0;
   }

   else
   {
      if (length > 0)
         png_crc_read(png_ptr, png_ptr->unknown_chunk.data, length);
      png_crc_finish(png_ptr, 0);
      return 1;
   }
}