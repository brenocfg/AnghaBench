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
typedef  int uint32 ;

/* Variables and functions */
 scalar_t__ FCEUI_IsMovieActive () ; 
 int /*<<< orphan*/  GUI_GetMouseState (int*,int*,int*) ; 
 int PtoV (int,int) ; 
 int SDL_BUTTON (int) ; 
 int SDL_GetMouseState (int*,int*) ; 

void GetMouseData(uint32 *d)
{
 if(FCEUI_IsMovieActive()<0)
   return;

 int x,y;
 uint32 t;

 t=SDL_GetMouseState(&x,&y);
 #ifdef EXTGUI
 GUI_GetMouseState(&t,&x,&y);
 #endif

 d[2]=0;
 if(t&SDL_BUTTON(1))
  d[2]|=1;
 if(t&SDL_BUTTON(3))
  d[2]|=2;
 t=PtoV(x,y); 
 d[0]=t&0xFFFF;
 d[1]=(t>>16)&0xFFFF;
}