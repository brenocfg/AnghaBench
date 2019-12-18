#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t png_uint_32 ;
struct TYPE_14__ {size_t text_length; int /*<<< orphan*/ * lang_key; int /*<<< orphan*/ * lang; scalar_t__ itxt_length; void* text; void* key; int /*<<< orphan*/  compression; } ;
typedef  TYPE_2__ png_text ;
typedef  TYPE_3__* png_structrp ;
typedef  int /*<<< orphan*/  png_inforp ;
typedef  char* png_const_charp ;
typedef  void* png_charp ;
typedef  scalar_t__* png_bytep ;
typedef  size_t png_alloc_size_t ;
struct TYPE_13__ {char* msg; } ;
struct TYPE_15__ {int user_chunk_cache_max; int mode; TYPE_1__ zstream; scalar_t__* read_buffer; } ;

/* Variables and functions */
 int PNG_AFTER_IDAT ; 
 scalar_t__ PNG_COMPRESSION_TYPE_BASE ; 
 int PNG_HAVE_IDAT ; 
 int PNG_HAVE_IHDR ; 
 size_t PNG_SIZE_MAX ; 
 int /*<<< orphan*/  PNG_TEXT_COMPRESSION_zTXt ; 
 scalar_t__ Z_STREAM_END ; 
 int /*<<< orphan*/  png_chunk_benign_error (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  png_chunk_error (TYPE_3__*,char*) ; 
 scalar_t__ png_crc_finish (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  png_crc_read (TYPE_3__*,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 scalar_t__ png_decompress_chunk (TYPE_3__*,size_t,size_t,size_t*,int) ; 
 scalar_t__* png_read_buffer (TYPE_3__*,size_t,int) ; 
 scalar_t__ png_set_text_2 (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*,int) ; 

void /* PRIVATE */
png_handle_zTXt(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
   png_const_charp errmsg = NULL;
   png_bytep       buffer;
   png_uint_32     keyword_length;

   png_debug(1, "in png_handle_zTXt");

#ifdef PNG_USER_LIMITS_SUPPORTED
   if (png_ptr->user_chunk_cache_max != 0)
   {
      if (png_ptr->user_chunk_cache_max == 1)
      {
         png_crc_finish(png_ptr, length);
         return;
      }

      if (--png_ptr->user_chunk_cache_max == 1)
      {
         png_crc_finish(png_ptr, length);
         png_chunk_benign_error(png_ptr, "no space in chunk cache");
         return;
      }
   }
#endif

   if ((png_ptr->mode & PNG_HAVE_IHDR) == 0)
      png_chunk_error(png_ptr, "missing IHDR");

   if ((png_ptr->mode & PNG_HAVE_IDAT) != 0)
      png_ptr->mode |= PNG_AFTER_IDAT;

   buffer = png_read_buffer(png_ptr, length, 2/*silent*/);

   if (buffer == NULL)
   {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "out of memory");
      return;
   }

   png_crc_read(png_ptr, buffer, length);

   if (png_crc_finish(png_ptr, 0) != 0)
      return;

   /* TODO: also check that the keyword contents match the spec! */
   for (keyword_length = 0;
      keyword_length < length && buffer[keyword_length] != 0;
      ++keyword_length)
      /* Empty loop to find end of name */ ;

   if (keyword_length > 79 || keyword_length < 1)
      errmsg = "bad keyword";

   /* zTXt must have some LZ data after the keyword, although it may expand to
    * zero bytes; we need a '\0' at the end of the keyword, the compression type
    * then the LZ data:
    */
   else if (keyword_length + 3 > length)
      errmsg = "truncated";

   else if (buffer[keyword_length+1] != PNG_COMPRESSION_TYPE_BASE)
      errmsg = "unknown compression type";

   else
   {
      png_alloc_size_t uncompressed_length = PNG_SIZE_MAX;

      /* TODO: at present png_decompress_chunk imposes a single application
       * level memory limit, this should be split to different values for iCCP
       * and text chunks.
       */
      if (png_decompress_chunk(png_ptr, length, keyword_length+2,
          &uncompressed_length, 1/*terminate*/) == Z_STREAM_END)
      {
         png_text text;

         /* It worked; png_ptr->read_buffer now looks like a tEXt chunk except
          * for the extra compression type byte and the fact that it isn't
          * necessarily '\0' terminated.
          */
         buffer = png_ptr->read_buffer;
         buffer[uncompressed_length+(keyword_length+2)] = 0;

         text.compression = PNG_TEXT_COMPRESSION_zTXt;
         text.key = (png_charp)buffer;
         text.text = (png_charp)(buffer + keyword_length+2);
         text.text_length = uncompressed_length;
         text.itxt_length = 0;
         text.lang = NULL;
         text.lang_key = NULL;

         if (png_set_text_2(png_ptr, info_ptr, &text, 1) != 0)
            errmsg = "insufficient memory";
      }

      else
         errmsg = png_ptr->zstream.msg;
   }

   if (errmsg != NULL)
      png_chunk_benign_error(png_ptr, errmsg);
}