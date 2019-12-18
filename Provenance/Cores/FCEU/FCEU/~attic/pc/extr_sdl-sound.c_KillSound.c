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
 scalar_t__ Buffer ; 
 int /*<<< orphan*/  FCEUI_Sound (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_CloseAudio () ; 
 int /*<<< orphan*/  SDL_INIT_AUDIO ; 
 int /*<<< orphan*/  SDL_QuitSubSystem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 

int KillSound(void)
{
 FCEUI_Sound(0);
 SDL_CloseAudio();
 SDL_QuitSubSystem(SDL_INIT_AUDIO);
 if(Buffer)
 {
  free(Buffer);
  Buffer = 0;
 }
 return(0);
}