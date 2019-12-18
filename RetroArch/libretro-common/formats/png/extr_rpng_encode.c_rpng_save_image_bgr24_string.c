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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  intfstream_t ;

/* Variables and functions */
 unsigned int DEFLATE_PADDING ; 
 int /*<<< orphan*/  GOTO_END_ERROR () ; 
 int PNG_ROUGH_HEADER ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_HINT_NONE ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_WRITE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int intfstream_get_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intfstream_open_writable_memory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intfstream_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  intfstream_rewind (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int rpng_save_image_stream (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned int,unsigned int,int,int) ; 

uint8_t* rpng_save_image_bgr24_string(const uint8_t *data,
      unsigned width, unsigned height, signed pitch, uint64_t* bytes)
{
   bool ret                    = false;
   uint8_t* buf                = NULL;
   uint8_t* output             = NULL;
   int buf_length              = 0;
   intfstream_t* intf_s        = NULL;

   buf_length = (int)(width*height*3*DEFLATE_PADDING)+PNG_ROUGH_HEADER;
   buf        = (uint8_t*)malloc(buf_length*sizeof(uint8_t));
   if (!buf)
      GOTO_END_ERROR(); 
   
   intf_s = intfstream_open_writable_memory(buf, 
         RETRO_VFS_FILE_ACCESS_WRITE,
         RETRO_VFS_FILE_ACCESS_HINT_NONE,
         buf_length);

   ret = rpng_save_image_stream((const uint8_t*)data, 
            intf_s, width, height, pitch, 3);

   *bytes = intfstream_get_ptr(intf_s);
   intfstream_rewind(intf_s);
   output = (uint8_t*)malloc((*bytes)*sizeof(uint8_t));
   if (!output)
      GOTO_END_ERROR();
   intfstream_read(intf_s, output, *bytes);

end:
   if (buf)
      free(buf);
   if (intf_s)
      free(intf_s);
   if (ret == false)
   {
      if (output)
         free(output);
      return NULL;
   }
   return output;
}