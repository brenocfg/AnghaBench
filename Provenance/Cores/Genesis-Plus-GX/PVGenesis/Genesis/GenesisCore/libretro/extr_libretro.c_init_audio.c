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
 int /*<<< orphan*/  audio_init (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntsc_fps ; 
 int /*<<< orphan*/  pal_fps ; 
 scalar_t__ vdp_pal ; 

__attribute__((used)) static void init_audio(void)
{
   audio_init(48000, vdp_pal ? pal_fps : ntsc_fps);
   //audio_init(44100, 0);
}