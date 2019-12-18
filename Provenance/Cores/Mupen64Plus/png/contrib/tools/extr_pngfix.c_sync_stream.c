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
struct file {int type; int read_count; int length; int /*<<< orphan*/  data_pos; TYPE_1__* global; int /*<<< orphan*/  status_code; } ;
typedef  int png_uint_32 ;
typedef  int png_byte ;
struct TYPE_2__ {scalar_t__ verbose; } ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  READ_ERROR_CODE ; 
 int /*<<< orphan*/  STREAM_ERROR ; 
 scalar_t__ chunk_type_valid (int) ; 
 int crc_init_4 (int) ; 
 int crc_one_byte (int,int) ; 
 int /*<<< orphan*/  file_setpos (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int get32 (int*,unsigned int) ; 
 int png_IEND ; 
 int /*<<< orphan*/  process_chunk (struct file*,int,int,int) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int read_4 (struct file*,int*) ; 
 int read_byte (struct file*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stop (struct file*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  type_name (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sync_stream(struct file *file)
   /* The stream seems to be messed up, attempt to resync from the current chunk
    * header.  Executes stop on a fatal error, otherwise calls process_chunk.
    */
{
   png_uint_32 file_crc;

   file->status_code |= STREAM_ERROR;

   if (file->global->verbose)
   {
      fputs(" SYNC ", stderr);
      type_name(file->type, stderr);
      putc('\n', stderr);
   }

   /* Return to the start of the chunk data */
   file_setpos(file, &file->data_pos);
   file->read_count = 8;

   if (read_4(file, &file_crc) == 4) /* else completely truncated */
   {
      /* Ignore the recorded chunk length, proceed through the data looking for
       * a leading sequence of bytes that match the CRC in the following four
       * bytes.  Each time a match is found check the next 8 bytes for a valid
       * length, chunk-type pair.
       */
      png_uint_32 length;
      png_uint_32 type = file->type;
      png_uint_32 crc = crc_init_4(type);
      png_byte buffer[8];
      unsigned int nread = 0, nused = 0;

      for (length=0; length <= 0x7fffffff; ++length)
      {
         int ch;

         if ((crc ^ 0xffffffff) == file_crc)
         {
            /* A match on the CRC; for IEND this is sufficient, but for anything
             * else expect a following chunk header.
             */
            if (type == png_IEND)
            {
               file->length = length;
               process_chunk(file, file_crc, 0, 0);
               return;
            }

            else
            {
               /* Need 8 bytes */
               while (nread < 8+nused)
               {
                  ch = read_byte(file);
                  if (ch == EOF)
                     goto truncated;
                  buffer[(nread++) & 7] = (png_byte)ch;
               }

               /* Prevent overflow */
               nread -= nused & ~7;
               nused -= nused & ~7; /* or, nused &= 7 ;-) */

               /* Examine the 8 bytes for a valid chunk header. */
               {
                  png_uint_32 next_length = get32(buffer, nused);

                  if (next_length < 0x7fffffff)
                  {
                     png_uint_32 next_type = get32(buffer, nused+4);

                     if (chunk_type_valid(next_type))
                     {
                        file->read_count -= 8;
                        process_chunk(file, file_crc, next_length, next_type);
                        return;
                     }
                  }

                  /* Not valid, keep going. */
               }
            }
         }

         /* This catches up with the circular buffer which gets filled above
          * while checking a chunk header.  This code is slightly tricky - if
          * the chunk_type is IEND the buffer will never be used, if it is not
          * the code will always read ahead exactly 8 bytes and pass this on to
          * process_chunk.  So the invariant that IEND leaves the file position
          * after the IEND CRC and other chunk leave it after the *next* chunk
          * header is not broken.
          */
         if (nread <= nused)
         {
            ch = read_byte(file);

            if (ch == EOF)
               goto truncated;
         }

         else
            ch = buffer[(++nused) & 7];

         crc = crc_one_byte(crc, file_crc >> 24);
         file_crc = (file_crc << 8) + ch;
      }

      /* Control gets to here if when 0x7fffffff bytes (plus 8) have been read,
       * ok, treat this as a damaged stream too:
       */
   }

truncated:
   stop(file, READ_ERROR_CODE, "damaged PNG stream");
}