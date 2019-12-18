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
typedef  int /*<<< orphan*/  FCEUGI ;

/* Variables and functions */
 int /*<<< orphan*/  InitJoysticks () ; 
 int /*<<< orphan*/  InitVideo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KillJoysticks () ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_QuitSubSystem (int /*<<< orphan*/ ) ; 
 scalar_t__ bcpj ; 
 scalar_t__ bcpv ; 

void ButtonConfigEnd(void)
{ 
 extern FCEUGI *CurGame;
 KillJoysticks();
 SDL_QuitSubSystem(SDL_INIT_VIDEO); 
 if(bcpv) InitVideo(CurGame);
 if(bcpj) InitJoysticks();
}