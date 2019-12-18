#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct PicoVideo {int* reg; } ;
struct TYPE_3__ {int frame_count; } ;
struct TYPE_4__ {TYPE_1__ m; struct PicoVideo video; } ;

/* Variables and functions */
 int /*<<< orphan*/  DrawAllSprites (unsigned char*,int,int) ; 
 int /*<<< orphan*/  DrawAllSpritesInterlace (int,int) ; 
 int /*<<< orphan*/  DrawLayer (int,int*,int,int) ; 
 size_t DrawScanline ; 
 int /*<<< orphan*/  DrawSpritesHiAS (unsigned char*,int) ; 
 int /*<<< orphan*/  DrawSpritesSHi (unsigned char*) ; 
 int /*<<< orphan*/  DrawTilesFromCache (int*,int,int) ; 
 int /*<<< orphan*/  DrawWindow (int,int,int,int) ; 
 int* HighCacheA ; 
 int* HighCacheB ; 
 unsigned char** HighLnSpr ; 
 int PDRAW_INTERLACE ; 
 int PDRAW_LAYERA_ON ; 
 int PDRAW_LAYERB_ON ; 
 int PDRAW_PLANE_HI_PRIO ; 
 int PDRAW_SHHI_DONE ; 
 int PDRAW_SPRITES_HI_ON ; 
 int PDRAW_SPRITES_LOW_ON ; 
 int POPT_ACC_SPRITES ; 
 TYPE_2__ Pico ; 
 int PicoDrawMask ; 
 int PicoOpt ; 
 unsigned char SPRL_HAVE_HI ; 
 unsigned char SPRL_HAVE_LO ; 
 unsigned char SPRL_MAY_HAVE_OP ; 
 int /*<<< orphan*/  printf (char*,int,size_t,int,int) ; 
 int rendstatus ; 

__attribute__((used)) static int DrawDisplay(int sh)
{
  unsigned char *sprited = &HighLnSpr[DrawScanline][0];
  struct PicoVideo *pvid=&Pico.video;
  int win=0,edge=0,hvwind=0;
  int maxw,maxcells;

  rendstatus &= ~(PDRAW_SHHI_DONE|PDRAW_PLANE_HI_PRIO);

  if (pvid->reg[12]&1) {
    maxw = 328; maxcells = 40;
  } else {
    maxw = 264; maxcells = 32;
  }

  // Find out if the window is on this line:
  win=pvid->reg[0x12];
  edge=(win&0x1f)<<3;

  if (win&0x80) { if (DrawScanline>=edge) hvwind=1; }
  else          { if (DrawScanline< edge) hvwind=1; }

  if (!hvwind) // we might have a vertical window here
  {
    win=pvid->reg[0x11];
    edge=win&0x1f;
    if (win&0x80) {
      if (!edge) hvwind=1;
      else if(edge < (maxcells>>1)) hvwind=2;
    } else {
      if (!edge);
      else if(edge < (maxcells>>1)) hvwind=2;
      else hvwind=1;
    }
  }

  /* - layer B low - */
  if (PicoDrawMask & PDRAW_LAYERB_ON)
    DrawLayer(1|(sh<<1), HighCacheB, 0, maxcells);
  /* - layer A low - */
  if (!(PicoDrawMask & PDRAW_LAYERA_ON));
  else if (hvwind == 1)
    DrawWindow(0, maxcells>>1, 0, sh);
  else if (hvwind == 2) {
    DrawLayer(0|(sh<<1), HighCacheA, (win&0x80) ?    0 : edge<<1, (win&0x80) ?     edge<<1 : maxcells);
    DrawWindow(                      (win&0x80) ? edge :       0, (win&0x80) ? maxcells>>1 : edge, 0, sh);
  } else
    DrawLayer(0|(sh<<1), HighCacheA, 0, maxcells);
  /* - sprites low - */
  if (!(PicoDrawMask & PDRAW_SPRITES_LOW_ON));
  else if (rendstatus & PDRAW_INTERLACE)
    DrawAllSpritesInterlace(0, sh);
  else if (sprited[1] & SPRL_HAVE_LO)
    DrawAllSprites(sprited, 0, sh);

  /* - layer B hi - */
  if ((PicoDrawMask & PDRAW_LAYERB_ON) && HighCacheB[0])
    DrawTilesFromCache(HighCacheB, sh, maxw);
  /* - layer A hi - */
  if (!(PicoDrawMask & PDRAW_LAYERA_ON));
  else if (hvwind == 1)
    DrawWindow(0, maxcells>>1, 1, sh);
  else if (hvwind == 2) {
    if (HighCacheA[0]) DrawTilesFromCache(HighCacheA, sh, (win&0x80) ? edge<<4 : maxw);
    DrawWindow((win&0x80) ? edge : 0, (win&0x80) ? maxcells>>1 : edge, 1, sh);
  } else
    if (HighCacheA[0]) DrawTilesFromCache(HighCacheA, sh, maxw);
  /* - sprites hi - */
  if (!(PicoDrawMask & PDRAW_SPRITES_HI_ON));
  else if (rendstatus & PDRAW_INTERLACE)
    DrawAllSpritesInterlace(1, sh);
  // have sprites without layer pri bit ontop of sprites with that bit
  else if ((sprited[1] & 0xd0) == 0xd0 && (PicoOpt & POPT_ACC_SPRITES))
    DrawSpritesHiAS(sprited, sh);
  else if (sh && (sprited[1] & SPRL_MAY_HAVE_OP))
    DrawSpritesSHi(sprited);
  else if (sprited[1] & SPRL_HAVE_HI)
    DrawAllSprites(sprited, 1, 0);

#if 0
  {
    int *c, a, b;
    for (a = 0, c = HighCacheA; *c; c++, a++);
    for (b = 0, c = HighCacheB; *c; c++, b++);
    printf("%i:%03i: a=%i, b=%i\n", Pico.m.frame_count, DrawScanline, a, b);
  }
#endif

  return 0;
}