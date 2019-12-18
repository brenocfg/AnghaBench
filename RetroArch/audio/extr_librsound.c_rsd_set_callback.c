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
struct TYPE_3__ {size_t cb_max_size; int /*<<< orphan*/  error_callback; scalar_t__ audio_callback; void* cb_data; } ;
typedef  TYPE_1__ rsound_t ;
typedef  int /*<<< orphan*/  rsd_error_callback_t ;
typedef  scalar_t__ rsd_audio_callback_t ;

/* Variables and functions */
 int /*<<< orphan*/  retro_assert (int /*<<< orphan*/ ) ; 

void rsd_set_callback(rsound_t *rsound, rsd_audio_callback_t audio_cb, rsd_error_callback_t err_cb, size_t max_size, void *userdata)
{
   retro_assert(rsound != NULL);

   rsound->audio_callback = audio_cb;
   rsound->error_callback = err_cb;
   rsound->cb_max_size = max_size;
   rsound->cb_data = userdata;

   if (rsound->audio_callback)
   {
      retro_assert(rsound->error_callback);
   }
}