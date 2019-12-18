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
struct TYPE_2__ {int /*<<< orphan*/  s_device; int /*<<< orphan*/  s_default; } ;

/* Variables and functions */
 int /*<<< orphan*/  DI_Close () ; 
 int /*<<< orphan*/  audio_shutdown () ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  config_save () ; 
 int /*<<< orphan*/  gx_audio_Shutdown () ; 
 int /*<<< orphan*/  gx_video_Shutdown () ; 
 int /*<<< orphan*/  slot_autosave (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void shutdown(void)
{
  /* save current config */
  config_save();

  /* auto-save State file */
  slot_autosave(config.s_default,config.s_device);

  /* shutdown emulation */
  audio_shutdown();
  gx_audio_Shutdown();
  gx_video_Shutdown();
#ifdef HW_RVL
  DI_Close();
#endif
}