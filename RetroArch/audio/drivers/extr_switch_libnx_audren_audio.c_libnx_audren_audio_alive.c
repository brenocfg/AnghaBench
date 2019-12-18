#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  libnx_audren_t ;

/* Variables and functions */

__attribute__((used)) static bool libnx_audren_audio_alive(void *data)
{
   libnx_audren_t *aud = (libnx_audren_t*)data;

   if (!aud)
      return false;

   return true;
}