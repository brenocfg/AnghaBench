#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ png_uint_32 ;
typedef  int /*<<< orphan*/  png_structrp ;
typedef  scalar_t__ png_size_t ;
typedef  char* png_const_charp ;
typedef  int /*<<< orphan*/ * png_const_bytep ;
typedef  int /*<<< orphan*/  png_byte ;

/* Variables and functions */
 scalar_t__ PNG_UINT_31_MAX ; 
 scalar_t__ png_check_keyword (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  png_tEXt ; 
 int /*<<< orphan*/  png_write_chunk_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  png_write_chunk_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_write_chunk_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 

void /* PRIVATE */
png_write_tEXt(png_structrp png_ptr, png_const_charp key, png_const_charp text,
    png_size_t text_len)
{
   png_uint_32 key_len;
   png_byte new_key[80];

   png_debug(1, "in png_write_tEXt");

   key_len = png_check_keyword(png_ptr, key, new_key);

   if (key_len == 0)
      png_error(png_ptr, "tEXt: invalid keyword");

   if (text == NULL || *text == '\0')
      text_len = 0;

   else
      text_len = strlen(text);

   if (text_len > PNG_UINT_31_MAX - (key_len+1))
      png_error(png_ptr, "tEXt: text too long");

   /* Make sure we include the 0 after the key */
   png_write_chunk_header(png_ptr, png_tEXt,
       (png_uint_32)/*checked above*/(key_len + text_len + 1));
   /*
    * We leave it to the application to meet PNG-1.0 requirements on the
    * contents of the text.  PNG-1.0 through PNG-1.2 discourage the use of
    * any non-Latin-1 characters except for NEWLINE.  ISO PNG will forbid them.
    * The NUL character is forbidden by PNG-1.0 through PNG-1.2 and ISO PNG.
    */
   png_write_chunk_data(png_ptr, new_key, key_len + 1);

   if (text_len != 0)
      png_write_chunk_data(png_ptr, (png_const_bytep)text, text_len);

   png_write_chunk_end(png_ptr);
}