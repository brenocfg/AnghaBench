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
struct TYPE_2__ {int /*<<< orphan*/  mvoice; } ;
typedef  TYPE_1__ ax_audio_t ;

/* Variables and functions */
 int /*<<< orphan*/  AXSetMultiVoiceState (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AX_VOICE_STATE_STOPPED ; 

__attribute__((used)) static bool ax_audio_stop(void* data)
{
   ax_audio_t* ax = (ax_audio_t*)data;

   AXSetMultiVoiceState(ax->mvoice, AX_VOICE_STATE_STOPPED);
   return true;
}