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
struct TYPE_2__ {int* next_in; int avail_in; int* next_out; int avail_out; int /*<<< orphan*/ * msg; } ;
struct zlib {int state; int window_bits; int file_bits; int* header; int cksum; scalar_t__ ok_bits; scalar_t__ extra_bytes; scalar_t__ rewrite_offset; void* compressed_digits; int /*<<< orphan*/  compressed_bytes; void* uncompressed_digits; int /*<<< orphan*/  uncompressed_bytes; struct chunk* chunk; TYPE_1__ z; int /*<<< orphan*/  rc; struct file* file; } ;
struct file {int dummy; } ;
struct chunk {int* rewrite_buffer; int rewrite_length; scalar_t__ rewrite_offset; int /*<<< orphan*/  compressed_bytes; void* compressed_digits; int /*<<< orphan*/  uncompressed_bytes; void* uncompressed_digits; } ;
typedef  scalar_t__ png_uint_32 ;
typedef  int png_byte ;

/* Variables and functions */
 int ZLIB_FATAL ; 
 int ZLIB_OK ; 
 int ZLIB_STREAM_END ; 
 int ZLIB_TOO_FAR_BACK ; 
#define  Z_BUF_ERROR 132 
#define  Z_DATA_ERROR 131 
#define  Z_NEED_DICT 130 
 int Z_NO_FLUSH ; 
#define  Z_OK 129 
#define  Z_STREAM_END 128 
 int Z_SYNC_FLUSH ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  chunk_message (struct chunk*,char*) ; 
 int /*<<< orphan*/  inflate (TYPE_1__*,int) ; 
 int reread_byte (struct file*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,char*) ; 
 void* uarb_add32 (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 void* uarb_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  zlib_message (struct zlib*,int) ; 

__attribute__((used)) static int
zlib_advance(struct zlib *zlib, png_uint_32 nbytes)
   /* Read nbytes compressed bytes; the stream will be initialized if required.
    * Bytes are always being reread and errors are fatal.  The return code is as
    * follows:
    *
    *    -1: saw the "too far back" error
    *     0: ok, keep going
    *     1: saw Z_STREAM_END (zlib->extra_bytes indicates too much data)
    *     2: a zlib error that cannot be corrected (error message already
    *        output if required.)
    */
#  define ZLIB_TOO_FAR_BACK (-1)
#  define ZLIB_OK           0
#  define ZLIB_STREAM_END   1
#  define ZLIB_FATAL        2
{
   int state = zlib->state;
   int endrc = ZLIB_OK;
   png_uint_32 in_bytes = 0;
   struct file *file = zlib->file;

   assert(state >= 0);

   while (in_bytes < nbytes && endrc == ZLIB_OK)
   {
      png_uint_32 out_bytes;
      int flush;
      png_byte bIn = reread_byte(file);
      png_byte bOut;

      switch (state)
      {
         case 0: /* first header byte */
            {
               int file_bits = 8+(bIn >> 4);
               int new_bits = zlib->window_bits;

               zlib->file_bits = file_bits;

               /* Check against the existing value - it may not need to be
                * changed.  Note that a bogus file_bits is allowed through once,
                * to see if it works, but the window_bits value is set to 15,
                * the maximum.
                */
               if (new_bits == 0) /* no change */
                  zlib->window_bits = ((file_bits > 15) ? 15 : file_bits);

               else if (new_bits != file_bits) /* rewrite required */
                  bIn = (png_byte)((bIn & 0xf) + ((new_bits-8) << 4));
            }

            zlib->header[0] = bIn;
            zlib->state = state = 1;
            break;

         case 1: /* second header byte */
            {
               int b2 = bIn & 0xe0; /* top 3 bits */

               /* The checksum calculation, on the first 11 bits: */
               b2 += 0x1f - ((zlib->header[0] << 8) + b2) % 0x1f;

               /* Update the checksum byte if required: */
               if (bIn != b2)
               {
                  /* If the first byte wasn't changed this indicates an error in
                   * the checksum calculation; signal this by setting 'cksum'.
                   */
                  if (zlib->file_bits == zlib->window_bits)
                     zlib->cksum = 1;

                  bIn = (png_byte)b2;
               }
            }

            zlib->header[1] = bIn;
            zlib->state = state = 2;
            break;

         default: /* After the header bytes */
            break;
      }

      /* For some streams, perhaps only those compressed with 'superfast
       * compression' (which results in a lot of copying) Z_BUF_ERROR can happen
       * immediately after all output has been flushed on the next input byte.
       * This is handled below when Z_BUF_ERROR is detected by adding an output
       * byte.
       */
      zlib->z.next_in = &bIn;
      zlib->z.avail_in = 1;
      zlib->z.next_out = &bOut;
      zlib->z.avail_out = 0;     /* Initially */

      /* Initially use Z_NO_FLUSH in an attempt to persuade zlib to look at this
       * byte without confusing what is going on with output.
       */
      flush = Z_NO_FLUSH;
      out_bytes = 0;

      /* NOTE: expression 3 is only evaluted on 'continue', because of the
       * 'break' at the end of this loop below.
       */
      for (;endrc == ZLIB_OK;
         flush = Z_SYNC_FLUSH,
         zlib->z.next_out = &bOut,
         zlib->z.avail_out = 1,
         ++out_bytes)
      {
         zlib->rc = inflate(&zlib->z, flush);
         out_bytes -= zlib->z.avail_out;

         switch (zlib->rc)
         {
            case Z_BUF_ERROR:
               if (zlib->z.avail_out == 0)
                  continue; /* Try another output byte. */

               if (zlib->z.avail_in == 0)
                  break; /* Try another input byte */

               /* Both avail_out and avail_in are 1 yet zlib returned a code
                * indicating no progress was possible.  This is unexpected.
                */
               zlib_message(zlib, 1/*unexpected*/);
               endrc = ZLIB_FATAL; /* stop processing */
               break;

            case Z_OK:
               /* Zlib is supposed to have made progress: */
               assert(zlib->z.avail_out == 0 || zlib->z.avail_in == 0);
               continue;

            case Z_STREAM_END:
               /* This is the successful end. */
               zlib->state = 3; /* end of stream */
               endrc = ZLIB_STREAM_END;
               break;

            case Z_NEED_DICT:
               zlib_message(zlib, 0/*stream error*/);
               endrc = ZLIB_FATAL;
               break;

            case Z_DATA_ERROR:
               /* The too far back error can be corrected, others cannot: */
               if (zlib->z.msg != NULL &&
                  strcmp(zlib->z.msg, "invalid distance too far back") == 0)
               {
                  endrc = ZLIB_TOO_FAR_BACK;
                  break;
               }
               /* FALL THROUGH */

            default:
               zlib_message(zlib, 0/*stream error*/);
               endrc = ZLIB_FATAL;
               break;
         } /* switch (inflate rc) */

         /* Control gets here when further output is not possible; endrc may
          * still be ZLIB_OK if more input is required.
          */
         break;
      } /* for (output bytes) */

      /* Keep a running count of output byte produced: */
      zlib->uncompressed_digits = uarb_add32(zlib->uncompressed_bytes,
         zlib->uncompressed_digits, out_bytes);

      /* Keep going, the loop will terminate when endrc is no longer set to
       * ZLIB_OK or all the input bytes have been consumed; meanwhile keep
       * adding input bytes.
       */
      assert(zlib->z.avail_in == 0 || endrc != ZLIB_OK);

      in_bytes += 1 - zlib->z.avail_in;
   } /* while (input bytes) */

   assert(in_bytes == nbytes || endrc != ZLIB_OK);

   /* Update the running total of input bytes consumed */
   zlib->compressed_digits = uarb_add32(zlib->compressed_bytes,
      zlib->compressed_digits, in_bytes - zlib->z.avail_in);

   /* At the end of the stream update the chunk with the accumulated
    * information if it is an improvement:
    */
   if (endrc == ZLIB_STREAM_END && zlib->window_bits < zlib->ok_bits)
   {
      struct chunk *chunk = zlib->chunk;

      chunk->uncompressed_digits = uarb_copy(chunk->uncompressed_bytes,
         zlib->uncompressed_bytes, zlib->uncompressed_digits);
      chunk->compressed_digits = uarb_copy(chunk->compressed_bytes,
         zlib->compressed_bytes, zlib->compressed_digits);
      chunk->rewrite_buffer[0] = zlib->header[0];
      chunk->rewrite_buffer[1] = zlib->header[1];

      if (zlib->window_bits != zlib->file_bits || zlib->cksum)
      {
         /* A rewrite is required */
         chunk->rewrite_offset = zlib->rewrite_offset;
         chunk->rewrite_length = 2;
      }

      else
      {
         chunk->rewrite_offset = 0;
         chunk->rewrite_length = 0;
      }

      if (in_bytes < nbytes)
         chunk_message(chunk, "extra compressed data");

      zlib->extra_bytes = nbytes - in_bytes;
      zlib->ok_bits = zlib->window_bits;
   }

   return endrc;
}