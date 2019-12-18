#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct file {int write_count; scalar_t__ type; TYPE_1__* chunk; } ;
typedef  scalar_t__ png_uint_32 ;
struct TYPE_2__ {scalar_t__ chunk_type; } ;

/* Variables and functions */
 int LIBPNG_ERROR_CODE ; 
 scalar_t__ png_IDAT ; 

__attribute__((used)) static png_uint_32
current_type(struct file *file, int code)
   /* Guess the actual chunk type that causes a stop() */
{
   /* This may return png_IDAT for errors detected (late) in the header; that
    * includes any inter-chunk consistency check that libpng performs.  Assume
    * that if the chunk_type is png_IDAT and the file write count is 8 this is
    * what is happening.
    */
   if (file->chunk != NULL)
   {
      png_uint_32 type = file->chunk->chunk_type;

      /* This is probably wrong for the excess IDATs case, because then libpng
       * whines about too many of them (apparently in some cases erroneously)
       * when the header is read.
       */
      if (code <= LIBPNG_ERROR_CODE && type == png_IDAT &&
         file->write_count == 8)
         type = 0; /* magic */

      return type;
   }

   else
      return file->type;
}