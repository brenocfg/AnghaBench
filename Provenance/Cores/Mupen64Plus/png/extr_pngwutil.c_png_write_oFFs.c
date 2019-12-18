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
typedef  int /*<<< orphan*/  png_structrp ;
typedef  int /*<<< orphan*/  png_size_t ;
typedef  int /*<<< orphan*/  png_int_32 ;
typedef  scalar_t__ png_byte ;

/* Variables and functions */
 int PNG_OFFSET_LAST ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_oFFs ; 
 int /*<<< orphan*/  png_save_int_32 (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_warning (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  png_write_complete_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 

void /* PRIVATE */
png_write_oFFs(png_structrp png_ptr, png_int_32 x_offset, png_int_32 y_offset,
    int unit_type)
{
   png_byte buf[9];

   png_debug(1, "in png_write_oFFs");

   if (unit_type >= PNG_OFFSET_LAST)
      png_warning(png_ptr, "Unrecognized unit type for oFFs chunk");

   png_save_int_32(buf, x_offset);
   png_save_int_32(buf + 4, y_offset);
   buf[8] = (png_byte)unit_type;

   png_write_complete_chunk(png_ptr, png_oFFs, buf, (png_size_t)9);
}