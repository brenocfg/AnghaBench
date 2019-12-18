#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int png_uint_32 ;
typedef  scalar_t__ png_structp ;
typedef  int png_size_t ;
struct TYPE_8__ {scalar_t__ pread; scalar_t__ readpos; TYPE_1__* current; int /*<<< orphan*/ * next; } ;
struct TYPE_7__ {scalar_t__ buffer_count; scalar_t__ buffer_position; TYPE_3__ this; } ;
typedef  TYPE_2__ png_modifier ;
typedef  int /*<<< orphan*/  png_infop ;
typedef  int /*<<< orphan*/  png_byte ;
struct TYPE_6__ {scalar_t__ datacount; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  modifier_read_imp (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  png_error (scalar_t__,char*) ; 
 int /*<<< orphan*/  png_process_data (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int store_read_buffer_avail (TYPE_3__*) ; 

__attribute__((used)) static void
modifier_progressive_read(png_modifier *pm, png_structp pp, png_infop pi)
{
   if (pm->this.pread != pp || pm->this.current == NULL ||
       pm->this.next == NULL)
      png_error(pp, "store state damaged (progressive)");

   /* This is another Horowitz and Hill random noise generator.  In this case
    * the aim is to stress the progressive reader with truly horrible variable
    * buffer sizes in the range 1..500, so a sequence of 9 bit random numbers
    * is generated.  We could probably just count from 1 to 32767 and get as
    * good a result.
    */
   for (;;)
   {
      static png_uint_32 noise = 1;
      png_size_t cb, cbAvail;
      png_byte buffer[512];

      /* Generate 15 more bits of stuff: */
      noise = (noise << 9) | ((noise ^ (noise >> (9-5))) & 0x1ff);
      cb = noise & 0x1ff;

      /* Check that this number of bytes are available (in the current buffer.)
       * (This doesn't quite work - the modifier might delete a chunk; unlikely
       * but possible, it doesn't happen at present because the modifier only
       * adds chunks to standard images.)
       */
      cbAvail = store_read_buffer_avail(&pm->this);
      if (pm->buffer_count > pm->buffer_position)
         cbAvail += pm->buffer_count - pm->buffer_position;

      if (cb > cbAvail)
      {
         /* Check for EOF: */
         if (cbAvail == 0)
            break;

         cb = cbAvail;
      }

      modifier_read_imp(pm, buffer, cb);
      png_process_data(pp, pi, buffer, cb);
   }

   /* Check the invariants at the end (if this fails it's a problem in this
    * file!)
    */
   if (pm->buffer_count > pm->buffer_position ||
       pm->this.next != &pm->this.current->data ||
       pm->this.readpos < pm->this.current->datacount)
      png_error(pp, "progressive read implementation error");
}