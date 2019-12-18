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
struct TYPE_6__ {scalar_t__ read; scalar_t__ draw; scalar_t__ context; } ;
struct TYPE_5__ {scalar_t__ read; scalar_t__ draw; scalar_t__ context; } ;
struct TYPE_7__ {int high_priority; int async_error_notification; scalar_t__ glgeterror_hack; scalar_t__ merge_end; scalar_t__ merge_pos; TYPE_2__ openvg; TYPE_1__ opengl; int /*<<< orphan*/  bound_api; int /*<<< orphan*/  error; } ;
typedef  TYPE_3__ CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_OPENGL_ES_API ; 
 int /*<<< orphan*/  EGL_SUCCESS ; 

void client_thread_state_init(CLIENT_THREAD_STATE_T *state)
{
   state->error = EGL_SUCCESS;

   state->bound_api = EGL_OPENGL_ES_API;

   state->opengl.context = 0;
   state->opengl.draw = 0;
   state->opengl.read = 0;

   state->openvg.context = 0;
   state->openvg.draw = 0;
   state->openvg.read = 0;

   state->high_priority = false;

   state->merge_pos = 0;
   state->merge_end = 0;

	state->glgeterror_hack = 0;
	state->async_error_notification = false;
}