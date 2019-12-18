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
 int /*<<< orphan*/  TileFlip (int,int,int) ; 
 int /*<<< orphan*/  TileNorm (int,int,int) ; 

__attribute__((used)) static void DrawSpriteInterlace(unsigned int *sprite)
{
  int width=0,height=0;
  int row=0,code=0;
  int pal;
  int tile=0,delta=0;
  int sx, sy;

  // parse the sprite data
  sy=sprite[0];
  height=sy>>24;
  sy=(sy&0x3ff)-0x100; // Y
  width=(height>>2)&3; height&=3;
  width++; height++; // Width and height in tiles

  row=(DrawScanline<<1)-sy; // Row of the sprite we are on

  code=sprite[1];
  sx=((code>>16)&0x1ff)-0x78; // X

  if (code&0x1000) row^=(16<<height)-1; // Flip Y

  tile=code&0x3ff; // Tile number
  tile+=row>>4; // Tile number increases going down
  delta=height; // Delta to increase tile by going right
  if (code&0x0800) { tile+=delta*(width-1); delta=-delta; } // Flip X

  tile<<=5; tile+=(row&15)<<1; // Tile address

  delta<<=5; // Delta of address
  pal=((code>>9)&0x30); // Get palette pointer

  for (; width; width--,sx+=8,tile+=delta)
  {
    if(sx<=0)   continue;
    if(sx>=328) break; // Offscreen

    tile&=0x7fff; // Clip tile address
    if (code&0x0800) TileFlip(sx,tile,pal);
    else             TileNorm(sx,tile,pal);
  }
}