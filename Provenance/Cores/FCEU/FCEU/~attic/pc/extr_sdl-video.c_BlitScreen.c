#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_15__ {int w; int h; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_14__ {int w; int h; int pitch; int flags; scalar_t__ pixels; } ;
typedef  TYPE_1__ SDL_Surface ;
typedef  TYPE_2__ SDL_Rect ;

/* Variables and functions */
 int /*<<< orphan*/  Blit8To8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Blit8ToHigh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int) ; 
 TYPE_1__* BlitBuf ; 
 int /*<<< orphan*/  BlitOpenGL (int /*<<< orphan*/ *) ; 
 int NOFFSET ; 
 int NWIDTH ; 
 int /*<<< orphan*/  RedoPalette () ; 
 int /*<<< orphan*/  SDL_BlitSurface (TYPE_1__*,TYPE_2__*,TYPE_1__*,TYPE_2__*) ; 
 int SDL_DOUBLEBUF ; 
 int /*<<< orphan*/  SDL_Flip (TYPE_1__*) ; 
 scalar_t__ SDL_LockSurface (TYPE_1__*) ; 
 scalar_t__ SDL_MUSTLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  SDL_UnlockSurface (TYPE_1__*) ; 
 int /*<<< orphan*/  SDL_UpdateRect (TYPE_1__*,int,int,int,int) ; 
 scalar_t__ _fullscreen ; 
 int curbpp ; 
 int /*<<< orphan*/  eefx ; 
 int exs ; 
 int eys ; 
 scalar_t__ paletterefresh ; 
 TYPE_1__* screen ; 
 int /*<<< orphan*/  sponge ; 
 int srendline ; 
 int tlines ; 
 scalar_t__ usingogl ; 

void BlitScreen(uint8 *XBuf)
{
 SDL_Surface *TmpScreen;
 uint8 *dest;
 int xo=0,yo=0;

 if(!screen) return;

 if(paletterefresh)
 {
  RedoPalette();
  paletterefresh=0;
 }

 #ifdef OPENGL
 if(usingogl)
 {
  BlitOpenGL(XBuf);
  return;
 }
 #endif

 XBuf+=srendline*256;

 if(BlitBuf) TmpScreen=BlitBuf;
 else TmpScreen=screen;

 if(SDL_MUSTLOCK(TmpScreen))
  if(SDL_LockSurface(TmpScreen))
  {   
   return;
  }

 dest=(uint8*)TmpScreen->pixels;

 if(_fullscreen)
 {
  xo=(((TmpScreen->w-NWIDTH*exs))/2);
  dest+=xo*(curbpp>>3);
  if(TmpScreen->h>(tlines*eys))
  {
   yo=((TmpScreen->h-tlines*eys)/2);
   dest+=yo*TmpScreen->pitch;
  }
 }

 if(curbpp>8)
 {
  if(BlitBuf)
   Blit8ToHigh(XBuf+NOFFSET,dest, NWIDTH, tlines, TmpScreen->pitch,1,1);
  else
   Blit8ToHigh(XBuf+NOFFSET,dest, NWIDTH, tlines, TmpScreen->pitch,exs,eys);
 }
 else
 {
  if(BlitBuf)
   Blit8To8(XBuf+NOFFSET,dest, NWIDTH, tlines, TmpScreen->pitch,1,1,0,sponge);
  else
   Blit8To8(XBuf+NOFFSET,dest, NWIDTH, tlines, TmpScreen->pitch,exs,eys,eefx,sponge);
 }
 if(SDL_MUSTLOCK(TmpScreen))
  SDL_UnlockSurface(TmpScreen);

 if(BlitBuf)
 {
  SDL_Rect srect;
  SDL_Rect drect;

  srect.x=0;
  srect.y=0;
  srect.w=NWIDTH;
  srect.h=tlines;

  drect.x=0;
  drect.y=0;
  drect.w=exs*NWIDTH;
  drect.h=eys*tlines;

  SDL_BlitSurface(BlitBuf, &srect,screen,&drect);
 }

 SDL_UpdateRect(screen, xo, yo, NWIDTH*exs, tlines*eys);

 if(screen->flags&SDL_DOUBLEBUF)
  SDL_Flip(screen);
}