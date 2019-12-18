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
struct file {int type; int length; int crc; int /*<<< orphan*/  data_pos; struct chunk* chunk; void* interlace_method; void* filter_method; void* compression_method; void* color_type; void* bit_depth; void* height; void* width; int /*<<< orphan*/  (* alloc ) (struct file*,int) ;int /*<<< orphan*/ * idat; TYPE_1__* global; int /*<<< orphan*/  status_code; } ;
struct chunk {int const chunk_type; int chunk_length; scalar_t__ rewrite_offset; scalar_t__ rewrite_length; } ;
typedef  int png_uint_32 ;
struct TYPE_2__ {int verbose; scalar_t__ skip; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRC_ERROR ; 
 scalar_t__ CRITICAL (int const) ; 
 int /*<<< orphan*/  READ_ERROR_CODE ; 
 scalar_t__ SKIP_BAD_CRC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  calc_image_size (struct file*) ; 
 int /*<<< orphan*/  chunk_end (struct chunk**) ; 
 int /*<<< orphan*/  file_setpos (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned long,int,int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpos (struct file*) ; 
#define  png_IDAT 132 
#define  png_IHDR 131 
#define  png_iCCP 130 
#define  png_iTXt 129 
#define  png_zTXt 128 
 int /*<<< orphan*/  process_IDAT (struct file*) ; 
 int /*<<< orphan*/  process_iTXt (struct file*) ; 
 int /*<<< orphan*/  process_zTXt_iCCP (struct file*) ; 
 int /*<<< orphan*/  read_chunk (struct file*) ; 
 void* reread_4 (struct file*) ; 
 void* reread_byte (struct file*) ; 
 int /*<<< orphan*/  setpos (struct chunk*) ; 
 scalar_t__ skip_chunk_type (TYPE_1__*,int const) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stop (struct file*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stop_invalid (struct file*,char*) ; 
 int /*<<< orphan*/  stub1 (struct file*,int) ; 
 int /*<<< orphan*/  stub2 (struct file*,int) ; 
 int /*<<< orphan*/  type_message (struct file*,int const,char*) ; 
 int /*<<< orphan*/  type_name (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_chunk(struct file *file, png_uint_32 file_crc, png_uint_32 next_length,
   png_uint_32 next_type)
   /* Called when the chunk data has been read, next_length and next_type
    * will be set for the next chunk (or 0 if this is IEND).
    *
    * When this routine returns, chunk_length and chunk_type will be set for the
    * next chunk to write because if a chunk is skipped this return calls back
    * to read_chunk.
    */
{
   const png_uint_32 type = file->type;

   if (file->global->verbose > 1)
   {
      fputs("  ", stderr);
      type_name(file->type, stderr);
      fprintf(stderr, " %lu 0x%.8x 0x%.8x\n", (unsigned long)file->length,
         file->crc ^ 0xffffffff, file_crc);
   }

   /* The basic structure seems correct but the CRC may not match, in this
    * case assume that it is simply a bad CRC, either wrongly calculated or
    * because of damaged stream data.
    */
   if ((file->crc ^ 0xffffffff) != file_crc)
   {
      /* The behavior is set by the 'skip' setting; if it is anything other
       * than SKIP_BAD_CRC ignore the bad CRC and return the chunk, with a
       * corrected CRC and possibly processed, to libpng.  Otherwise skip the
       * chunk, which will result in a fatal error if the chunk is critical.
       */
      file->status_code |= CRC_ERROR;

      /* Ignore the bad CRC  */
      if (file->global->skip != SKIP_BAD_CRC)
         type_message(file, type, "bad CRC");

      /* This will cause an IEND with a bad CRC to stop */
      else if (CRITICAL(type))
         stop(file, READ_ERROR_CODE, "bad CRC in critical chunk");

      else
      {
         type_message(file, type, "skipped: bad CRC");

         /* NOTE: this cannot be reached for IEND because it is critical. */
         goto skip_chunk;
      }
   }

   /* Check for other 'skip' cases and handle these; these only apply to
    * ancillary chunks (and not tRNS, which should probably have been a critical
    * chunk.)
    */
   if (skip_chunk_type(file->global, type))
      goto skip_chunk;

   /* The chunk may still be skipped if problems are detected in the LZ data,
    * however the LZ data check requires a chunk.  Handle this by instantiating
    * a chunk unless an IDAT is already instantiated (IDAT control structures
    * instantiate their own chunk.)
    */
   if (type != png_IDAT)
      file->alloc(file, 0/*chunk*/);

   else if (file->idat == NULL)
      file->alloc(file, 1/*IDAT*/);

   else
   {
      /* The chunk length must be updated for process_IDAT */
      assert(file->chunk != NULL);
      assert(file->chunk->chunk_type == png_IDAT);
      file->chunk->chunk_length = file->length;
   }

   /* Record the 'next' information too, now that the original values for
    * this chunk have been copied.  Notice that the IDAT chunks only make a
    * copy of the position of the first chunk, this is fine - process_IDAT does
    * not need the position of this chunk.
    */
   file->length = next_length;
   file->type = next_type;
   getpos(file);

   /* Do per-type processing, note that if this code does not return from the
    * function the chunk will be skipped.  The rewrite is cancelled here so that
    * it can be set in the per-chunk processing.
    */
   file->chunk->rewrite_length = 0;
   file->chunk->rewrite_offset = 0;
   switch (type)
   {
      default:
         return;

      case png_IHDR:
         /* Read this now and update the control structure with the information
          * it contains.  The header is validated completely to ensure this is a
          * PNG.
          */
         {
            struct chunk *chunk = file->chunk;

            if (chunk->chunk_length != 13)
               stop_invalid(file, "IHDR length");

            /* Read all the IHDR information and validate it. */
            setpos(chunk);
            file->width = reread_4(file);
            file->height = reread_4(file);
            file->bit_depth = reread_byte(file);
            file->color_type = reread_byte(file);
            file->compression_method = reread_byte(file);
            file->filter_method = reread_byte(file);
            file->interlace_method = reread_byte(file);

            /* This validates all the fields, and calls stop_invalid if
             * there is a problem.
             */
            calc_image_size(file);
         }
         return;

         /* Ancillary chunks that require further processing: */
      case png_zTXt: case png_iCCP:
         if (process_zTXt_iCCP(file))
            return;
         chunk_end(&file->chunk);
         file_setpos(file, &file->data_pos);
         break;

      case png_iTXt:
         if (process_iTXt(file))
            return;
         chunk_end(&file->chunk);
         file_setpos(file, &file->data_pos);
         break;

      case png_IDAT:
         if (process_IDAT(file))
            return;
         /* First pass: */
         assert(next_type == png_IDAT);
         break;
   }

   /* Control reaches this point if the chunk must be skipped.  For chunks other
    * than IDAT this means that the zlib compressed data is fatally damanged and
    * the chunk will not be passed to libpng.  For IDAT it means that the end of
    * the IDAT stream has not yet been reached and we must handle the next
    * (IDAT) chunk.  If the LZ data in an IDAT stream cannot be read 'stop' must
    * be used to halt parsing of the PNG.
    */
   read_chunk(file);
   return;

   /* This is the generic code to skip the current chunk; simply jump to the
    * next one.
    */
skip_chunk:
   file->length = next_length;
   file->type = next_type;
   getpos(file);
   read_chunk(file);
}