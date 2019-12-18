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
struct TYPE_2__ {int is_paused; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ gx_audio_t ;

/* Variables and functions */
 int /*<<< orphan*/  AIStopDMA () ; 
 int /*<<< orphan*/  DCFlushRange (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool gx_audio_stop(void *data)
{
   gx_audio_t *wa = (gx_audio_t*)data;

   if (!wa)
      return false;

   AIStopDMA();
   memset(wa->data, 0, sizeof(wa->data));
   DCFlushRange(wa->data, sizeof(wa->data));
   wa->is_paused = true;
   return true;
}