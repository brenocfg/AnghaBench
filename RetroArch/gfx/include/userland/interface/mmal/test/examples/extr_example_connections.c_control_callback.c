#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct CONTEXT_T {int /*<<< orphan*/  semaphore; int /*<<< orphan*/  eos; int /*<<< orphan*/  status; } ;
struct TYPE_7__ {scalar_t__ cmd; scalar_t__ data; } ;
struct TYPE_6__ {scalar_t__ userdata; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_1__ MMAL_PORT_T ;
typedef  TYPE_2__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 scalar_t__ MMAL_EVENT_EOS ; 
 scalar_t__ MMAL_EVENT_ERROR ; 
 int /*<<< orphan*/  MMAL_TRUE ; 
 int /*<<< orphan*/  mmal_buffer_header_release (TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_semaphore_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void control_callback(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
   struct CONTEXT_T *ctx = (struct CONTEXT_T *)port->userdata;

   if (buffer->cmd == MMAL_EVENT_ERROR)
      ctx->status = *(MMAL_STATUS_T *)buffer->data;
   else if (buffer->cmd == MMAL_EVENT_EOS)
      ctx->eos = MMAL_TRUE;

   mmal_buffer_header_release(buffer);

   /* The processing is done in our main thread */
   vcos_semaphore_post(&ctx->semaphore);
}