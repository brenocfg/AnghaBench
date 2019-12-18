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
 int DrawScanline ; 
 int /*<<< orphan*/  DrawSpritesSHi (unsigned char*) ; 
 scalar_t__ HighCol ; 
 int* HighPreSpr ; 
 int /*<<< orphan*/  PDRAW_SPR_LO_ON_HI ; 
 unsigned char SPRL_MAY_HAVE_OP ; 
 int TileFlipAS (int,int,int) ; 
 int TileFlipAS_noop (int,int,int) ; 
 int TileFlipAS_onlymark (int,int,int) ; 
 int TileNormAS (int,int,int) ; 
 int TileNormAS_noop (int,int,int) ; 
 int TileNormAS_onlymark (int,int,int) ; 
 int /*<<< orphan*/  rendstatus ; 

__attribute__((used)) static void DrawSpritesHiAS(unsigned char *sprited, int sh)
{
  int (*fTileFunc)(int sx,int addr,int pal);
  unsigned char *p;
  int entry, cnt, sh_cnt = 0;

  cnt = sprited[0] & 0x7f;
  if (cnt == 0) return;

  rendstatus |= PDRAW_SPR_LO_ON_HI;

  p = &sprited[3];

  // Go through sprites:
  for (entry = 0; entry < cnt; entry++)
  {
    int *sprite, code, pal, tile, sx, sy;
    int offs, delta, width, height, row;

    offs = (p[entry] & 0x7f) * 2;
    sprite = HighPreSpr + offs;
    code = sprite[1];
    pal = (code>>9)&0x30;

    if (code & 0x8000) // hi priority
    {
      if (sh && pal == 0x30)
      {
        if (code&0x800) fTileFunc=TileFlipAS_noop;
        else            fTileFunc=TileNormAS_noop;
      } else {
        if (code&0x800) fTileFunc=TileFlipAS;
        else            fTileFunc=TileNormAS;
      }
    } else {
      if (code&0x800) fTileFunc=TileFlipAS_onlymark;
      else            fTileFunc=TileNormAS_onlymark;
    }
    if (sh && pal == 0x30)
      p[sh_cnt++] = offs / 2; // re-save for sh/hi pass

    // parse remaining sprite data
    sy=sprite[0];
    sx=code>>16; // X
    width=sy>>28;
    height=(sy>>24)&7; // Width and height in tiles
    sy=(sy<<16)>>16; // Y

    row=DrawScanline-sy; // Row of the sprite we are on

    if (code&0x1000) row=(height<<3)-1-row; // Flip Y

    tile=code + (row>>3); // Tile number increases going down
    delta=height; // Delta to increase tile by going right
    if (code&0x0800) { tile+=delta*(width-1); delta=-delta; } // Flip X

    tile &= 0x7ff; tile<<=4; tile+=(row&7)<<1; // Tile address
    delta<<=4; // Delta of address

    pal |= 0x80;
    for (; width; width--,sx+=8,tile+=delta)
    {
      if(sx<=0)   continue;
      if(sx>=328) break; // Offscreen

      tile&=0x7fff; // Clip tile address
      fTileFunc(sx,tile,pal);
    }
  }

  if (!sh || !(sprited[1]&SPRL_MAY_HAVE_OP)) return;

  /* nasty 1: remove 'sprite' flags */
  {
    int c = 320/4/4, *zb = (int *)(HighCol+8);
    while (c--)
    {
      *zb++ &= 0x7f7f7f7f; *zb++ &= 0x7f7f7f7f;
      *zb++ &= 0x7f7f7f7f; *zb++ &= 0x7f7f7f7f;
    }
  }

  /* nasty 2: sh operator pass */
  sprited[0] = sh_cnt;
  DrawSpritesSHi(sprited);
}