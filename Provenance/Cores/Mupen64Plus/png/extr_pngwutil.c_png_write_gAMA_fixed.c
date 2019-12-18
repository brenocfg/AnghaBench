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
typedef  int /*<<< orphan*/  png_uint_32 ;
typedef  int /*<<< orphan*/  png_structrp ;
typedef  int /*<<< orphan*/  png_size_t ;
typedef  scalar_t__ png_fixed_point ;
typedef  int /*<<< orphan*/  png_byte ;

/* Variables and functions */
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_gAMA ; 
 int /*<<< orphan*/  png_save_uint_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_write_complete_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void /* PRIVATE */
png_write_gAMA_fixed(png_structrp png_ptr, png_fixed_point file_gamma)
{
   png_byte buf[4];

   png_debug(1, "in png_write_gAMA");

   /* file_gamma is saved in 1/100,000ths */
   png_save_uint_32(buf, (png_uint_32)file_gamma);
   png_write_complete_chunk(png_ptr, png_gAMA, buf, (png_size_t)4);
}