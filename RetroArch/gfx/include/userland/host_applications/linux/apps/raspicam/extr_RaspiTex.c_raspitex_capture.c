#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int request; size_t size; int /*<<< orphan*/  start_sem; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  completed_sem; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__ capture; } ;
typedef  TYPE_2__ RASPITEX_STATE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raspitexutil_brga_to_rgba (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  vcos_log_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_semaphore_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_semaphore_wait (int /*<<< orphan*/ *) ; 
 int write_tga (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

int raspitex_capture(RASPITEX_STATE *state, FILE *output_file)
{
   int rc = 0;
   uint8_t *buffer = NULL;
   size_t size = 0;

   vcos_log_trace("%s: state %p file %p", VCOS_FUNCTION,
                  state, output_file);

   if (state && output_file)
   {
      /* Only request one capture at a time */
      vcos_semaphore_wait(&state->capture.start_sem);
      state->capture.request = 1;

      /* Wait for capture to start */
      vcos_semaphore_wait(&state->capture.completed_sem);

      /* Take ownership of the captured buffer */
      buffer = state->capture.buffer;
      size = state->capture.size;

      state->capture.request = 0;
      state->capture.buffer = 0;
      state->capture.size = 0;

      /* Allow another capture to be requested */
      vcos_semaphore_post(&state->capture.start_sem);
   }
   if (size == 0 || ! buffer)
   {
      vcos_log_error("%s: capture failed", VCOS_FUNCTION);
      rc = -1;
      goto end;
   }

   raspitexutil_brga_to_rgba(buffer, size);
   rc = write_tga(output_file, state->width, state->height, buffer, size);
   fflush(output_file);

end:
   free(buffer);
   return rc;
}