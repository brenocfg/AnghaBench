#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * msg; } ;
struct zlib {int ok_bits; TYPE_2__ z; int /*<<< orphan*/  chunk; int /*<<< orphan*/  cksum; int /*<<< orphan*/  uncompressed_digits; int /*<<< orphan*/  uncompressed_bytes; int /*<<< orphan*/  file_bits; int /*<<< orphan*/  window_bits; TYPE_1__* global; } ;
struct file {int /*<<< orphan*/  status_code; int /*<<< orphan*/  chunk; int /*<<< orphan*/  idat; } ;
typedef  int /*<<< orphan*/  png_uint_32 ;
typedef  int /*<<< orphan*/  fpos_t ;
struct TYPE_3__ {int /*<<< orphan*/  optimize_zlib; } ;

/* Variables and functions */
 void* PNGZ_MSG_CAST (char*) ; 
 int /*<<< orphan*/  TOO_FAR_BACK ; 
#define  ZLIB_OK 130 
#define  ZLIB_STREAM_END 129 
#define  ZLIB_TOO_FAR_BACK 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  chunk_message (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  file_getpos (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_setpos (struct file*,int /*<<< orphan*/ *) ; 
 int max_window_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlib_end (struct zlib*) ; 
 scalar_t__ zlib_init (struct zlib*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlib_message (struct zlib*,int /*<<< orphan*/ ) ; 
 scalar_t__ zlib_reset (struct zlib*,int) ; 
 int zlib_run (struct zlib*) ; 

__attribute__((used)) static int /* global function; not a member function */
zlib_check(struct file *file, png_uint_32 offset)
   /* Check the stream of zlib compressed data in either idat (if given) or (if
    * not) chunk.  In fact it is zlib_run that handles the difference in reading
    * a single chunk and a list of IDAT chunks.
    *
    * In either case the input file must be positioned at the first byte of zlib
    * compressed data (the first header byte).
    *
    * The return value is true on success, including the case where the zlib
    * header may need to be rewritten, and false on an unrecoverable error.
    *
    * In the case of IDAT chunks 'offset' should be 0.
    */
{
   fpos_t start_pos;
   struct zlib zlib;

   /* Record the start of the LZ data to allow a re-read. */
   file_getpos(file, &start_pos);

   /* First test the existing (file) window bits: */
   if (zlib_init(&zlib, file->idat, file->chunk, 0/*window bits*/, offset))
   {
      int min_bits, max_bits, rc;

      /* The first run using the existing window bits. */
      rc = zlib_run(&zlib);

      switch (rc)
      {
         case ZLIB_TOO_FAR_BACK:
            /* too far back error */
            file->status_code |= TOO_FAR_BACK;
            min_bits = zlib.window_bits + 1;
            max_bits = 15;
            break;

         case ZLIB_STREAM_END:
            if (!zlib.global->optimize_zlib &&
               zlib.window_bits == zlib.file_bits && !zlib.cksum)
            {
               /* The trivial case where the stream is ok and optimization was
                * not requested.
                */
               zlib_end(&zlib);
               return 1;
            }

            max_bits = max_window_bits(zlib.uncompressed_bytes,
               zlib.uncompressed_digits);
            if (zlib.ok_bits < max_bits)
               max_bits = zlib.ok_bits;
            min_bits = 8;

            /* cksum is set if there is an error in the zlib header checksum
             * calculation in the original file (and this may be the only reason
             * a rewrite is required).  We can't rely on the file window bits in
             * this case, so do the optimization anyway.
             */
            if (zlib.cksum)
               chunk_message(zlib.chunk, "zlib checkum");
            break;


         case ZLIB_OK:
            /* Truncated stream; unrecoverable, gets converted to ZLIB_FATAL */
            zlib.z.msg = PNGZ_MSG_CAST("[truncated]");
            zlib_message(&zlib, 0/*expected*/);
            /* FALL THROUGH */

         default:
            /* Unrecoverable error; skip the chunk; a zlib_message has already
             * been output.
             */
            zlib_end(&zlib);
            return 0;
      }

      /* Optimize window bits or fix a too-far-back error.  min_bits and
       * max_bits have been set appropriately, ok_bits records the bit value
       * known to work.
       */
      while (min_bits < max_bits || max_bits < zlib.ok_bits/*if 16*/)
      {
         int test_bits = (min_bits + max_bits) >> 1;

         if (zlib_reset(&zlib, test_bits))
         {
            file_setpos(file, &start_pos);
            rc = zlib_run(&zlib);

            switch (rc)
            {
               case ZLIB_TOO_FAR_BACK:
                  min_bits = test_bits+1;
                  if (min_bits > max_bits)
                  {
                     /* This happens when the stream really is damaged and it
                      * contains a distance code that addresses bytes before
                      * the start of the uncompressed data.
                      */
                     assert(test_bits == 15);

                     /* Output the error that wasn't output before: */
                     if (zlib.z.msg == NULL)
                        zlib.z.msg = PNGZ_MSG_CAST(
                           "invalid distance too far back");
                     zlib_message(&zlib, 0/*stream error*/);
                     zlib_end(&zlib);
                     return 0;
                  }
                  break;

               case ZLIB_STREAM_END: /* success */
                  max_bits = test_bits;
                  break;

               default:
                  /* A fatal error; this happens if a too-far-back error was
                   * hiding a more serious error, zlib_advance has already
                   * output a zlib_message.
                   */
                  zlib_end(&zlib);
                  return 0;
            }
         }

         else /* inflateReset2 failed */
         {
            zlib_end(&zlib);
            return 0;
         }
      }

      /* The loop guarantees this */
      assert(zlib.ok_bits == max_bits);
      zlib_end(&zlib);
      return 1;
   }

   else /* zlib initialization failed - skip the chunk */
   {
      zlib_end(&zlib);
      return 0;
   }
}