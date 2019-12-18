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
 int TileFlip (int,int,int) ; 
 int TileFlipSH_markop (int,int,int) ; 
 int TileNorm (int,int,int) ; 
 int TileNormSH_markop (int,int,int) ; 

__attribute__((used)) static void DrawSprite(int *sprite, int sh)
{
  int width=0,height=0;
  int row=0,code=0;
  int pal;
  int tile=0,delta=0;
  int sx, sy;
  int (*fTileFunc)(int sx,int addr,int pal);

  // parse the sprite data
  sy=sprite[0];
  code=sprite[1];
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

  pal=(code>>9)&0x30;
  pal|=sh<<6;

  if (sh && (code&0x6000) == 0x6000) {
    if(code&0x0800) fTileFunc=TileFlipSH_markop;
    else            fTileFunc=TileNormSH_markop;
  } else {
    if(code&0x0800) fTileFunc=TileFlip;
    else            fTileFunc=TileNorm;
  }

  for (; width; width--,sx+=8,tile+=delta)
  {
    if(sx<=0)   continue;
    if(sx>=328) break; // Offscreen

    tile&=0x7fff; // Clip tile address
    fTileFunc(sx,tile,pal);
  }
}