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
typedef  int /*<<< orphan*/  gx_audio_t ;

/* Variables and functions */
 int /*<<< orphan*/  AIRegisterDMACallback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AIStopDMA () ; 
 int /*<<< orphan*/  free (void*) ; 
 int stop_audio ; 

__attribute__((used)) static void gx_audio_free(void *data)
{
   gx_audio_t *wa = (gx_audio_t*)data;

   if (!wa)
      return;

   stop_audio = true;
   AIStopDMA();
   AIRegisterDMACallback(NULL);

   free(data);
}