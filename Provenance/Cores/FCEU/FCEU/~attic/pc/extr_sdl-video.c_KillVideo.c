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
 scalar_t__ IconSurface ; 
 int /*<<< orphan*/  KillBlitToHigh () ; 
 int /*<<< orphan*/  KillOpenGL () ; 
 int /*<<< orphan*/  SDL_FreeSurface (scalar_t__) ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_QuitSubSystem (int /*<<< orphan*/ ) ; 
 int curbpp ; 
 int inited ; 
 scalar_t__ usingogl ; 

int KillVideo(void)
{
 if(IconSurface)
 {
  SDL_FreeSurface(IconSurface);
  IconSurface=0;
 }

 if(inited&1)
 {
  #ifdef OPENGL
  if(usingogl)
   KillOpenGL();
  else
  #endif
  if(curbpp>8)
   KillBlitToHigh();
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
  inited&=~1;
  return(1);
 }
 inited=0;
 return(0);
}