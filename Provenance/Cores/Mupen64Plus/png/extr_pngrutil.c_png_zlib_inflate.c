#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_structrp ;
struct TYPE_5__ {scalar_t__ avail_in; int* next_in; char* msg; } ;
struct TYPE_4__ {TYPE_3__ zstream; scalar_t__ zstream_start; } ;

/* Variables and functions */
 int Z_DATA_ERROR ; 
 int inflate (TYPE_3__*,int) ; 

int /* PRIVATE */
png_zlib_inflate(png_structrp png_ptr, int flush)
{
   if (png_ptr->zstream_start && png_ptr->zstream.avail_in > 0)
   {
      if ((*png_ptr->zstream.next_in >> 4) > 7)
      {
         png_ptr->zstream.msg = "invalid window size (libpng)";
         return Z_DATA_ERROR;
      }

      png_ptr->zstream_start = 0;
   }

   return inflate(&png_ptr->zstream, flush);
}