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
typedef  int png_uint_32 ;
typedef  int /*<<< orphan*/  png_structrp ;

/* Variables and functions */
 int /*<<< orphan*/  png_chunk_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 

void /* PRIVATE */
png_check_chunk_name(png_structrp png_ptr, png_uint_32 chunk_name)
{
   int i;

   png_debug(1, "in png_check_chunk_name");

   for (i=1; i<=4; ++i)
   {
      int c = chunk_name & 0xff;

      if (c < 65 || c > 122 || (c > 90 && c < 97))
         png_chunk_error(png_ptr, "invalid chunk type");

      chunk_name >>= 8;
   }
}