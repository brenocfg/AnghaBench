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

/* Variables and functions */
 int /*<<< orphan*/  audio_shutdown () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_ntsc ; 
 int /*<<< orphan*/  sms_ntsc ; 

void retro_deinit(void)
{
   audio_shutdown();
#if defined(USE_NTSC)
   free(md_ntsc);
   free(sms_ntsc);
#endif
}