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
typedef  int /*<<< orphan*/  SDL_Surface ;

/* Variables and functions */
 int /*<<< orphan*/  FCEUD_Message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitJoysticks () ; 
 int /*<<< orphan*/  KillJoysticks () ; 
 int /*<<< orphan*/  KillVideo () ; 
 int /*<<< orphan*/  SDL_GetError () ; 
 int SDL_INIT_VIDEO ; 
 int SDL_InitSubSystem (int) ; 
 int /*<<< orphan*/  SDL_QuitSubSystem (int) ; 
 int /*<<< orphan*/ * SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_WM_SetCaption (char*,int /*<<< orphan*/ ) ; 
 int SDL_WasInit (int) ; 
 int /*<<< orphan*/  bcpj ; 
 int /*<<< orphan*/  bcpv ; 

int ButtonConfigBegin(void)
{
 SDL_Surface *screen;
 SDL_QuitSubSystem(SDL_INIT_VIDEO);
 bcpv=KillVideo();
 bcpj=KillJoysticks();
 
 if(!(SDL_WasInit(SDL_INIT_VIDEO)&SDL_INIT_VIDEO))
  if(SDL_InitSubSystem(SDL_INIT_VIDEO)==-1)
  {
   FCEUD_Message(SDL_GetError());
   return(0);
  } 
 
 screen = SDL_SetVideoMode(300, 1, 8, 0); 
 SDL_WM_SetCaption("Button Config",0);
 InitJoysticks();
 
 return(1);
}