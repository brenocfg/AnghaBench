#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int preview_stop; int /*<<< orphan*/  preview_queue; } ;
typedef  TYPE_1__ RASPITEX_STATE ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/ * mmal_queue_get (int /*<<< orphan*/ ) ; 
 int raspitex_draw (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_log_error (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int preview_process_returned_bufs(RASPITEX_STATE* state)
{
   MMAL_BUFFER_HEADER_T *buf;
   int new_frame = 0;
   int rc = 0;

   while ((buf = mmal_queue_get(state->preview_queue)) != NULL)
   {
      if (state->preview_stop == 0)
      {
         new_frame = 1;
         rc = raspitex_draw(state, buf);
         if (rc != 0)
         {
            vcos_log_error("%s: Error drawing frame. Stopping.", VCOS_FUNCTION);
            state->preview_stop = 1;
            return rc;
         }
      }
   }

   /* If there were no new frames then redraw the scene again with the previous
    * texture. Otherwise, go round the loop again to see if any new buffers
    * are returned.
    */
   if (! new_frame)
      rc = raspitex_draw(state, NULL);
   return rc;
}