#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ png_uint_32 ;
typedef  TYPE_1__* png_structrp ;
typedef  int /*<<< orphan*/  png_byte ;
struct TYPE_4__ {int flags; int io_state; scalar_t__ crc; int /*<<< orphan*/  chunk_name; } ;

/* Variables and functions */
 scalar_t__ PNG_CHUNK_ANCILLARY (int /*<<< orphan*/ ) ; 
 int PNG_FLAG_CRC_ANCILLARY_MASK ; 
 int PNG_FLAG_CRC_ANCILLARY_NOWARN ; 
 int PNG_FLAG_CRC_ANCILLARY_USE ; 
 int PNG_FLAG_CRC_CRITICAL_IGNORE ; 
 int PNG_IO_CHUNK_CRC ; 
 int PNG_IO_READING ; 
 scalar_t__ png_get_uint_32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_read_data (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

int /* PRIVATE */
png_crc_error(png_structrp png_ptr)
{
   png_byte crc_bytes[4];
   png_uint_32 crc;
   int need_crc = 1;

   if (PNG_CHUNK_ANCILLARY(png_ptr->chunk_name) != 0)
   {
      if ((png_ptr->flags & PNG_FLAG_CRC_ANCILLARY_MASK) ==
          (PNG_FLAG_CRC_ANCILLARY_USE | PNG_FLAG_CRC_ANCILLARY_NOWARN))
         need_crc = 0;
   }

   else /* critical */
   {
      if ((png_ptr->flags & PNG_FLAG_CRC_CRITICAL_IGNORE) != 0)
         need_crc = 0;
   }

#ifdef PNG_IO_STATE_SUPPORTED
   png_ptr->io_state = PNG_IO_READING | PNG_IO_CHUNK_CRC;
#endif

   /* The chunk CRC must be serialized in a single I/O call. */
   png_read_data(png_ptr, crc_bytes, 4);

   if (need_crc != 0)
   {
      crc = png_get_uint_32(crc_bytes);
      return ((int)(crc != png_ptr->crc));
   }

   else
      return (0);
}