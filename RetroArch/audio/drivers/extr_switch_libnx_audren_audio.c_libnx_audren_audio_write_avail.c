#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t buffer_size; size_t current_size; int /*<<< orphan*/  current_wavebuf; } ;
typedef  TYPE_1__ libnx_audren_t ;

/* Variables and functions */

__attribute__((used)) static size_t libnx_audren_audio_write_avail(void *data)
{
   libnx_audren_t *aud = (libnx_audren_t*)data;
   size_t avail;

   if (!aud || !aud->current_wavebuf)
      return 0;

   avail = aud->buffer_size - aud->current_size;

   return avail;
}