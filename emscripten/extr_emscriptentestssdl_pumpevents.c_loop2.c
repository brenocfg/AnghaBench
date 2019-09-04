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
typedef  scalar_t__ Uint8 ;

/* Variables and functions */
 size_t SDLK_RIGHT ; 
 scalar_t__* SDL_GetKeyState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_PumpEvents () ; 

int loop2()
{
   unsigned i;
   int r = 0;
   
   // method 2: SDL_PumpEvents
   SDL_PumpEvents();

   const Uint8 *keys = SDL_GetKeyState(NULL);
   if (keys[SDLK_RIGHT])
      r = 2;

   return r;
}