#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ png_uint_32 ;
typedef  TYPE_1__* png_structrp ;
typedef  int /*<<< orphan*/  png_byte ;
struct TYPE_6__ {void* io_state; scalar_t__ chunk_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_CSTRING_FROM_CHUNK (int /*<<< orphan*/ *,scalar_t__) ; 
 void* PNG_IO_CHUNK_DATA ; 
 void* PNG_IO_CHUNK_HDR ; 
 void* PNG_IO_WRITING ; 
 int /*<<< orphan*/  png_calculate_crc (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  png_debug2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  png_reset_crc (TYPE_1__*) ; 
 int /*<<< orphan*/  png_save_uint_32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  png_write_data (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
png_write_chunk_header(png_structrp png_ptr, png_uint_32 chunk_name,
    png_uint_32 length)
{
   png_byte buf[8];

#if defined(PNG_DEBUG) && (PNG_DEBUG > 0)
   PNG_CSTRING_FROM_CHUNK(buf, chunk_name);
   png_debug2(0, "Writing %s chunk, length = %lu", buf, (unsigned long)length);
#endif

   if (png_ptr == NULL)
      return;

#ifdef PNG_IO_STATE_SUPPORTED
   /* Inform the I/O callback that the chunk header is being written.
    * PNG_IO_CHUNK_HDR requires a single I/O call.
    */
   png_ptr->io_state = PNG_IO_WRITING | PNG_IO_CHUNK_HDR;
#endif

   /* Write the length and the chunk name */
   png_save_uint_32(buf, length);
   png_save_uint_32(buf + 4, chunk_name);
   png_write_data(png_ptr, buf, 8);

   /* Put the chunk name into png_ptr->chunk_name */
   png_ptr->chunk_name = chunk_name;

   /* Reset the crc and run it over the chunk name */
   png_reset_crc(png_ptr);

   png_calculate_crc(png_ptr, buf + 4, 4);

#ifdef PNG_IO_STATE_SUPPORTED
   /* Inform the I/O callback that chunk data will (possibly) be written.
    * PNG_IO_CHUNK_DATA does NOT require a specific number of I/O calls.
    */
   png_ptr->io_state = PNG_IO_WRITING | PNG_IO_CHUNK_DATA;
#endif
}