#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  size_t png_uint_32 ;
typedef  TYPE_2__* png_structrp ;
typedef  size_t png_size_t ;
typedef  char* png_const_charp ;
typedef  int* png_const_bytep ;
typedef  int png_byte ;
struct TYPE_17__ {size_t input_len; size_t output_len; } ;
typedef  TYPE_3__ compression_state ;
struct TYPE_15__ {char* msg; } ;
struct TYPE_16__ {TYPE_1__ zstream; } ;

/* Variables and functions */
 int PNG_COMPRESSION_TYPE_BASE ; 
#define  PNG_ITXT_COMPRESSION_NONE 131 
#define  PNG_ITXT_COMPRESSION_zTXt 130 
#define  PNG_TEXT_COMPRESSION_NONE 129 
#define  PNG_TEXT_COMPRESSION_zTXt 128 
 size_t PNG_UINT_31_MAX ; 
 scalar_t__ Z_OK ; 
 size_t png_check_keyword (TYPE_2__*,char*,int*) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_error (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  png_iTXt ; 
 scalar_t__ png_text_compress (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  png_text_compress_init (TYPE_3__*,int*,size_t) ; 
 int /*<<< orphan*/  png_write_chunk_data (TYPE_2__*,int*,size_t) ; 
 int /*<<< orphan*/  png_write_chunk_end (TYPE_2__*) ; 
 int /*<<< orphan*/  png_write_chunk_header (TYPE_2__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  png_write_compressed_data_out (TYPE_2__*,TYPE_3__*) ; 
 size_t strlen (char*) ; 

void /* PRIVATE */
png_write_iTXt(png_structrp png_ptr, int compression, png_const_charp key,
    png_const_charp lang, png_const_charp lang_key, png_const_charp text)
{
   png_uint_32 key_len, prefix_len;
   png_size_t lang_len, lang_key_len;
   png_byte new_key[82];
   compression_state comp;

   png_debug(1, "in png_write_iTXt");

   key_len = png_check_keyword(png_ptr, key, new_key);

   if (key_len == 0)
      png_error(png_ptr, "iTXt: invalid keyword");

   /* Set the compression flag */
   switch (compression)
   {
      case PNG_ITXT_COMPRESSION_NONE:
      case PNG_TEXT_COMPRESSION_NONE:
         compression = new_key[++key_len] = 0; /* no compression */
         break;

      case PNG_TEXT_COMPRESSION_zTXt:
      case PNG_ITXT_COMPRESSION_zTXt:
         compression = new_key[++key_len] = 1; /* compressed */
         break;

      default:
         png_error(png_ptr, "iTXt: invalid compression");
   }

   new_key[++key_len] = PNG_COMPRESSION_TYPE_BASE;
   ++key_len; /* for the keywod separator */

   /* We leave it to the application to meet PNG-1.0 requirements on the
    * contents of the text.  PNG-1.0 through PNG-1.2 discourage the use of
    * any non-Latin-1 characters except for NEWLINE.  ISO PNG, however,
    * specifies that the text is UTF-8 and this really doesn't require any
    * checking.
    *
    * The NUL character is forbidden by PNG-1.0 through PNG-1.2 and ISO PNG.
    *
    * TODO: validate the language tag correctly (see the spec.)
    */
   if (lang == NULL) lang = ""; /* empty language is valid */
   lang_len = strlen(lang)+1;
   if (lang_key == NULL) lang_key = ""; /* may be empty */
   lang_key_len = strlen(lang_key)+1;
   if (text == NULL) text = ""; /* may be empty */

   prefix_len = key_len;
   if (lang_len > PNG_UINT_31_MAX-prefix_len)
      prefix_len = PNG_UINT_31_MAX;
   else
      prefix_len = (png_uint_32)(prefix_len + lang_len);

   if (lang_key_len > PNG_UINT_31_MAX-prefix_len)
      prefix_len = PNG_UINT_31_MAX;
   else
      prefix_len = (png_uint_32)(prefix_len + lang_key_len);

   png_text_compress_init(&comp, (png_const_bytep)text, strlen(text));

   if (compression != 0)
   {
      if (png_text_compress(png_ptr, png_iTXt, &comp, prefix_len) != Z_OK)
         png_error(png_ptr, png_ptr->zstream.msg);
   }

   else
   {
      if (comp.input_len > PNG_UINT_31_MAX-prefix_len)
         png_error(png_ptr, "iTXt: uncompressed text too long");

      /* So the string will fit in a chunk: */
      comp.output_len = (png_uint_32)/*SAFE*/comp.input_len;
   }

   png_write_chunk_header(png_ptr, png_iTXt, comp.output_len + prefix_len);

   png_write_chunk_data(png_ptr, new_key, key_len);

   png_write_chunk_data(png_ptr, (png_const_bytep)lang, lang_len);

   png_write_chunk_data(png_ptr, (png_const_bytep)lang_key, lang_key_len);

   if (compression != 0)
      png_write_compressed_data_out(png_ptr, &comp);

   else
      png_write_chunk_data(png_ptr, (png_const_bytep)text, comp.output_len);

   png_write_chunk_end(png_ptr);
}