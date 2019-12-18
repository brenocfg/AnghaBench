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
typedef  void* uInt ;
typedef  TYPE_2__* png_structrp ;
typedef  scalar_t__ png_size_t ;
typedef  int /*<<< orphan*/ * png_bytep ;
struct TYPE_9__ {scalar_t__ avail_in; scalar_t__ avail_out; scalar_t__ next_out; int /*<<< orphan*/ * next_in; } ;
struct TYPE_10__ {int flags; scalar_t__ row_buf; scalar_t__ row_number; scalar_t__ num_rows; int pass; TYPE_1__ zstream; scalar_t__ zowner; int /*<<< orphan*/  iwidth; int /*<<< orphan*/  pixel_depth; } ;

/* Variables and functions */
 int PNG_FLAG_ZSTREAM_ENDED ; 
 int PNG_INFLATE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ PNG_ROWBYTES (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int Z_DATA_ERROR ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  Z_SYNC_FLUSH ; 
 int /*<<< orphan*/  png_benign_error (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  png_error (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  png_push_process_row (TYPE_2__*) ; 
 int /*<<< orphan*/  png_warning (TYPE_2__*,char*) ; 

void /* PRIVATE */
png_process_IDAT_data(png_structrp png_ptr, png_bytep buffer,
    png_size_t buffer_length)
{
   /* The caller checks for a non-zero buffer length. */
   if (!(buffer_length > 0) || buffer == NULL)
      png_error(png_ptr, "No IDAT data (internal error)");

   /* This routine must process all the data it has been given
    * before returning, calling the row callback as required to
    * handle the uncompressed results.
    */
   png_ptr->zstream.next_in = buffer;
   /* TODO: WARNING: TRUNCATION ERROR: DANGER WILL ROBINSON: */
   png_ptr->zstream.avail_in = (uInt)buffer_length;

   /* Keep going until the decompressed data is all processed
    * or the stream marked as finished.
    */
   while (png_ptr->zstream.avail_in > 0 &&
      (png_ptr->flags & PNG_FLAG_ZSTREAM_ENDED) == 0)
   {
      int ret;

      /* We have data for zlib, but we must check that zlib
       * has someplace to put the results.  It doesn't matter
       * if we don't expect any results -- it may be the input
       * data is just the LZ end code.
       */
      if (!(png_ptr->zstream.avail_out > 0))
      {
         /* TODO: WARNING: TRUNCATION ERROR: DANGER WILL ROBINSON: */
         png_ptr->zstream.avail_out = (uInt)(PNG_ROWBYTES(png_ptr->pixel_depth,
             png_ptr->iwidth) + 1);

         png_ptr->zstream.next_out = png_ptr->row_buf;
      }

      /* Using Z_SYNC_FLUSH here means that an unterminated
       * LZ stream (a stream with a missing end code) can still
       * be handled, otherwise (Z_NO_FLUSH) a future zlib
       * implementation might defer output and therefore
       * change the current behavior (see comments in inflate.c
       * for why this doesn't happen at present with zlib 1.2.5).
       */
      ret = PNG_INFLATE(png_ptr, Z_SYNC_FLUSH);

      /* Check for any failure before proceeding. */
      if (ret != Z_OK && ret != Z_STREAM_END)
      {
         /* Terminate the decompression. */
         png_ptr->flags |= PNG_FLAG_ZSTREAM_ENDED;
         png_ptr->zowner = 0;

         /* This may be a truncated stream (missing or
          * damaged end code).  Treat that as a warning.
          */
         if (png_ptr->row_number >= png_ptr->num_rows ||
             png_ptr->pass > 6)
            png_warning(png_ptr, "Truncated compressed data in IDAT");

         else
         {
            if (ret == Z_DATA_ERROR)
               png_benign_error(png_ptr, "IDAT: ADLER32 checksum mismatch");
            else
               png_error(png_ptr, "Decompression error in IDAT");
         }

         /* Skip the check on unprocessed input */
         return;
      }

      /* Did inflate output any data? */
      if (png_ptr->zstream.next_out != png_ptr->row_buf)
      {
         /* Is this unexpected data after the last row?
          * If it is, artificially terminate the LZ output
          * here.
          */
         if (png_ptr->row_number >= png_ptr->num_rows ||
             png_ptr->pass > 6)
         {
            /* Extra data. */
            png_warning(png_ptr, "Extra compressed data in IDAT");
            png_ptr->flags |= PNG_FLAG_ZSTREAM_ENDED;
            png_ptr->zowner = 0;

            /* Do no more processing; skip the unprocessed
             * input check below.
             */
            return;
         }

         /* Do we have a complete row? */
         if (png_ptr->zstream.avail_out == 0)
            png_push_process_row(png_ptr);
      }

      /* And check for the end of the stream. */
      if (ret == Z_STREAM_END)
         png_ptr->flags |= PNG_FLAG_ZSTREAM_ENDED;
   }

   /* All the data should have been processed, if anything
    * is left at this point we have bytes of IDAT data
    * after the zlib end code.
    */
   if (png_ptr->zstream.avail_in > 0)
      png_warning(png_ptr, "Extra compression data in IDAT");
}