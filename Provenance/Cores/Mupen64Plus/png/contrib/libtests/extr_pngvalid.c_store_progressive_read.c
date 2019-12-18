#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int png_uint_32 ;
typedef  scalar_t__ png_structp ;
struct TYPE_5__ {scalar_t__ pread; int /*<<< orphan*/ * next; int /*<<< orphan*/ * current; } ;
typedef  TYPE_1__ png_store ;
typedef  int png_size_t ;
typedef  int /*<<< orphan*/  png_infop ;
typedef  int /*<<< orphan*/  png_byte ;

/* Variables and functions */
 int /*<<< orphan*/  png_error (scalar_t__,char*) ; 
 int /*<<< orphan*/  png_process_data (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ store_read_buffer_avail (TYPE_1__*) ; 
 scalar_t__ store_read_chunk (TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
store_progressive_read(png_store *ps, png_structp pp, png_infop pi)
{
   if (ps->pread != pp || ps->current == NULL || ps->next == NULL)
      png_error(pp, "store state damaged (progressive)");

   /* This is another Horowitz and Hill random noise generator.  In this case
    * the aim is to stress the progressive reader with truly horrible variable
    * buffer sizes in the range 1..500, so a sequence of 9 bit random numbers
    * is generated.  We could probably just count from 1 to 32767 and get as
    * good a result.
    */
   while (store_read_buffer_avail(ps) > 0)
   {
      static png_uint_32 noise = 2;
      png_size_t cb;
      png_byte buffer[512];

      /* Generate 15 more bits of stuff: */
      noise = (noise << 9) | ((noise ^ (noise >> (9-5))) & 0x1ff);
      cb = noise & 0x1ff;
      cb -= store_read_chunk(ps, buffer, cb, 1);
      png_process_data(pp, pi, buffer, cb);
   }
}