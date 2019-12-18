#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ uInt ;
typedef  TYPE_1__* png_structrp ;
typedef  int /*<<< orphan*/  png_const_bytep ;
typedef  int /*<<< orphan*/ * png_bytep ;
typedef  scalar_t__ png_alloc_size_t ;
struct TYPE_15__ {int /*<<< orphan*/ * output; int /*<<< orphan*/ * next; } ;
struct TYPE_13__ {char* msg; scalar_t__ avail_out; scalar_t__ avail_in; int /*<<< orphan*/ * next_out; int /*<<< orphan*/  next_in; } ;
struct TYPE_14__ {scalar_t__ zowner; scalar_t__ zbuffer_size; int mode; scalar_t__ compression_type; TYPE_11__ zstream; TYPE_4__* zbuffer_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNGZ_INPUT_CAST (int /*<<< orphan*/ ) ; 
 int PNG_AFTER_IDAT ; 
 int /*<<< orphan*/  PNG_COMPRESSION_BUFFER_SIZE (TYPE_1__*) ; 
 scalar_t__ PNG_COMPRESSION_TYPE_BASE ; 
 int PNG_HAVE_IDAT ; 
 scalar_t__ ZLIB_IO_MAX ; 
 int Z_FINISH ; 
 int Z_NO_FLUSH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int deflate (TYPE_11__*,int) ; 
 int /*<<< orphan*/  optimize_cmf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ png_IDAT ; 
 int /*<<< orphan*/  png_compression_bufferp ; 
 int png_deflate_claim (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_free_buffer_list (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  png_image_size (TYPE_1__*) ; 
 int /*<<< orphan*/  png_malloc (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* png_voidcast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_write_complete_chunk (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  png_zstream_error (TYPE_1__*,int) ; 

void /* PRIVATE */
png_compress_IDAT(png_structrp png_ptr, png_const_bytep input,
    png_alloc_size_t input_len, int flush)
{
   if (png_ptr->zowner != png_IDAT)
   {
      /* First time.   Ensure we have a temporary buffer for compression and
       * trim the buffer list if it has more than one entry to free memory.
       * If 'WRITE_COMPRESSED_TEXT' is not set the list will never have been
       * created at this point, but the check here is quick and safe.
       */
      if (png_ptr->zbuffer_list == NULL)
      {
         png_ptr->zbuffer_list = png_voidcast(png_compression_bufferp,
             png_malloc(png_ptr, PNG_COMPRESSION_BUFFER_SIZE(png_ptr)));
         png_ptr->zbuffer_list->next = NULL;
      }

      else
         png_free_buffer_list(png_ptr, &png_ptr->zbuffer_list->next);

      /* It is a terminal error if we can't claim the zstream. */
      if (png_deflate_claim(png_ptr, png_IDAT, png_image_size(png_ptr)) != Z_OK)
         png_error(png_ptr, png_ptr->zstream.msg);

      /* The output state is maintained in png_ptr->zstream, so it must be
       * initialized here after the claim.
       */
      png_ptr->zstream.next_out = png_ptr->zbuffer_list->output;
      png_ptr->zstream.avail_out = png_ptr->zbuffer_size;
   }

   /* Now loop reading and writing until all the input is consumed or an error
    * terminates the operation.  The _out values are maintained across calls to
    * this function, but the input must be reset each time.
    */
   png_ptr->zstream.next_in = PNGZ_INPUT_CAST(input);
   png_ptr->zstream.avail_in = 0; /* set below */
   for (;;)
   {
      int ret;

      /* INPUT: from the row data */
      uInt avail = ZLIB_IO_MAX;

      if (avail > input_len)
         avail = (uInt)input_len; /* safe because of the check */

      png_ptr->zstream.avail_in = avail;
      input_len -= avail;

      ret = deflate(&png_ptr->zstream, input_len > 0 ? Z_NO_FLUSH : flush);

      /* Include as-yet unconsumed input */
      input_len += png_ptr->zstream.avail_in;
      png_ptr->zstream.avail_in = 0;

      /* OUTPUT: write complete IDAT chunks when avail_out drops to zero. Note
       * that these two zstream fields are preserved across the calls, therefore
       * there is no need to set these up on entry to the loop.
       */
      if (png_ptr->zstream.avail_out == 0)
      {
         png_bytep data = png_ptr->zbuffer_list->output;
         uInt size = png_ptr->zbuffer_size;

         /* Write an IDAT containing the data then reset the buffer.  The
          * first IDAT may need deflate header optimization.
          */
#ifdef PNG_WRITE_OPTIMIZE_CMF_SUPPORTED
            if ((png_ptr->mode & PNG_HAVE_IDAT) == 0 &&
                png_ptr->compression_type == PNG_COMPRESSION_TYPE_BASE)
               optimize_cmf(data, png_image_size(png_ptr));
#endif

         png_write_complete_chunk(png_ptr, png_IDAT, data, size);
         png_ptr->mode |= PNG_HAVE_IDAT;

         png_ptr->zstream.next_out = data;
         png_ptr->zstream.avail_out = size;

         /* For SYNC_FLUSH or FINISH it is essential to keep calling zlib with
          * the same flush parameter until it has finished output, for NO_FLUSH
          * it doesn't matter.
          */
         if (ret == Z_OK && flush != Z_NO_FLUSH)
            continue;
      }

      /* The order of these checks doesn't matter much; it just affects which
       * possible error might be detected if multiple things go wrong at once.
       */
      if (ret == Z_OK) /* most likely return code! */
      {
         /* If all the input has been consumed then just return.  If Z_FINISH
          * was used as the flush parameter something has gone wrong if we get
          * here.
          */
         if (input_len == 0)
         {
            if (flush == Z_FINISH)
               png_error(png_ptr, "Z_OK on Z_FINISH with output space");

            return;
         }
      }

      else if (ret == Z_STREAM_END && flush == Z_FINISH)
      {
         /* This is the end of the IDAT data; any pending output must be
          * flushed.  For small PNG files we may still be at the beginning.
          */
         png_bytep data = png_ptr->zbuffer_list->output;
         uInt size = png_ptr->zbuffer_size - png_ptr->zstream.avail_out;

#ifdef PNG_WRITE_OPTIMIZE_CMF_SUPPORTED
         if ((png_ptr->mode & PNG_HAVE_IDAT) == 0 &&
             png_ptr->compression_type == PNG_COMPRESSION_TYPE_BASE)
            optimize_cmf(data, png_image_size(png_ptr));
#endif

         png_write_complete_chunk(png_ptr, png_IDAT, data, size);
         png_ptr->zstream.avail_out = 0;
         png_ptr->zstream.next_out = NULL;
         png_ptr->mode |= PNG_HAVE_IDAT | PNG_AFTER_IDAT;

         png_ptr->zowner = 0; /* Release the stream */
         return;
      }

      else
      {
         /* This is an error condition. */
         png_zstream_error(png_ptr, ret);
         png_error(png_ptr, png_ptr->zstream.msg);
      }
   }
}