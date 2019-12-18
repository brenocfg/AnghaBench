#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ png_uint_32 ;
typedef  TYPE_1__* png_structrp ;
typedef  int /*<<< orphan*/  png_const_bytep ;
struct TYPE_9__ {struct TYPE_9__* next; int /*<<< orphan*/  output; } ;
typedef  TYPE_2__ png_compression_buffer ;
struct TYPE_10__ {scalar_t__ output_len; int /*<<< orphan*/  output; } ;
typedef  TYPE_3__ compression_state ;
struct TYPE_8__ {scalar_t__ zbuffer_size; TYPE_2__* zbuffer_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  png_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_write_chunk_data (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
png_write_compressed_data_out(png_structrp png_ptr, compression_state *comp)
{
   png_uint_32 output_len = comp->output_len;
   png_const_bytep output = comp->output;
   png_uint_32 avail = (sizeof comp->output);
   png_compression_buffer *next = png_ptr->zbuffer_list;

   for (;;)
   {
      if (avail > output_len)
         avail = output_len;

      png_write_chunk_data(png_ptr, output, avail);

      output_len -= avail;

      if (output_len == 0 || next == NULL)
         break;

      avail = png_ptr->zbuffer_size;
      output = next->output;
      next = next->next;
   }

   /* This is an internal error; 'next' must have been NULL! */
   if (output_len > 0)
      png_error(png_ptr, "error writing ancillary chunked compressed data");
}