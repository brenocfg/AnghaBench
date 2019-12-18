#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct delta_frame {int used; scalar_t__ frame; int have_local; int* have_real; int /*<<< orphan*/ * simlated_input; int /*<<< orphan*/ * real_input; int /*<<< orphan*/ * resolved_input; scalar_t__ crc; } ;
struct TYPE_3__ {scalar_t__ other_frame_count; } ;
typedef  TYPE_1__ netplay_t ;

/* Variables and functions */
 size_t MAX_CLIENTS ; 
 size_t MAX_INPUT_DEVICES ; 
 int /*<<< orphan*/  clear_input (int /*<<< orphan*/ ) ; 

bool netplay_delta_frame_ready(netplay_t *netplay, struct delta_frame *delta,
   uint32_t frame)
{
   size_t i;
   if (delta->used)
   {
      if (delta->frame == frame)
         return true;
      /* We haven't even replayed this frame yet,
       * so we can't overwrite it! */
      if (netplay->other_frame_count <= delta->frame)
         return false;
   }

   delta->used  = true;
   delta->frame = frame;
   delta->crc   = 0;

   for (i = 0; i < MAX_INPUT_DEVICES; i++)
   {
      clear_input(delta->resolved_input[i]);
      clear_input(delta->real_input[i]);
      clear_input(delta->simlated_input[i]);
   }
   delta->have_local = false;
   for (i = 0; i < MAX_CLIENTS; i++)
      delta->have_real[i] = false;
   return true;
}