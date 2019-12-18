#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ sbit; } ;
typedef  TYPE_2__ sbit_modification ;
struct TYPE_5__ {int /*<<< orphan*/  pread; } ;
struct TYPE_7__ {scalar_t__ bit_depth; int colour_type; scalar_t__ buffer_position; scalar_t__ buffer_count; scalar_t__* buffer; TYPE_1__ this; } ;
typedef  TYPE_3__ png_modifier ;
typedef  int /*<<< orphan*/  png_modification ;
typedef  scalar_t__ png_byte ;

/* Variables and functions */
 int CHUNK_sBIT ; 
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  png_save_uint_32 (scalar_t__*,int) ; 

__attribute__((used)) static int
sbit_modify(png_modifier *pm, png_modification *me, int add)
{
   png_byte sbit = ((sbit_modification*)me)->sbit;
   if (pm->bit_depth > sbit)
   {
      int cb = 0;
      switch (pm->colour_type)
      {
         case 0:
            cb = 1;
            break;

         case 2:
         case 3:
            cb = 3;
            break;

         case 4:
            cb = 2;
            break;

         case 6:
            cb = 4;
            break;

         default:
            png_error(pm->this.pread,
               "unexpected colour type in sBIT modification");
      }

      png_save_uint_32(pm->buffer, cb);
      png_save_uint_32(pm->buffer+4, CHUNK_sBIT);

      while (cb > 0)
         (pm->buffer+8)[--cb] = sbit;

      return 1;
   }
   else if (!add)
   {
      /* Remove the sBIT chunk */
      pm->buffer_count = pm->buffer_position = 0;
      return 1;
   }
   else
      return 0; /* do nothing */
}