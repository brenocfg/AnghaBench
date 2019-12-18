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
struct TYPE_2__ {scalar_t__ buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_CloseAudio () ; 
 int /*<<< orphan*/  SDL_PauseAudio (int) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 TYPE_1__ sdl_sound ; 

__attribute__((used)) static void sdl_sound_close()
{
  SDL_PauseAudio(1);
  SDL_CloseAudio();
  if (sdl_sound.buffer) 
    free(sdl_sound.buffer);
}