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
typedef  int png_size_t ;
typedef  int /*<<< orphan*/  png_const_charp ;
typedef  scalar_t__ png_byte ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_debug1 (int,char*,unsigned int) ; 
 int /*<<< orphan*/  png_sCAL ; 
 int /*<<< orphan*/  png_warning (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  png_write_complete_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

void /* PRIVATE */
png_write_sCAL_s(png_structrp png_ptr, int unit, png_const_charp width,
    png_const_charp height)
{
   png_byte buf[64];
   png_size_t wlen, hlen, total_len;

   png_debug(1, "in png_write_sCAL_s");

   wlen = strlen(width);
   hlen = strlen(height);
   total_len = wlen + hlen + 2;

   if (total_len > 64)
   {
      png_warning(png_ptr, "Can't write sCAL (buffer too small)");
      return;
   }

   buf[0] = (png_byte)unit;
   memcpy(buf + 1, width, wlen + 1);      /* Append the '\0' here */
   memcpy(buf + wlen + 2, height, hlen);  /* Do NOT append the '\0' here */

   png_debug1(3, "sCAL total length = %u", (unsigned int)total_len);
   png_write_complete_chunk(png_ptr, png_sCAL, buf, total_len);
}