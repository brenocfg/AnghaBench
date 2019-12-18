#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TileStrip {int* hc; int cells; int xmask; int nametab; int line; int /*<<< orphan*/  hscroll; } ;
struct PicoVideo {int* reg; } ;
struct TYPE_2__ {int* vsram; int /*<<< orphan*/ * vram; struct PicoVideo video; } ;

/* Variables and functions */
 int DrawScanline ; 
 int /*<<< orphan*/  DrawStrip (struct TileStrip*,int,int) ; 
 int /*<<< orphan*/  DrawStripInterlace (struct TileStrip*) ; 
 int /*<<< orphan*/  DrawStripVSRam (struct TileStrip*,int,int) ; 
 TYPE_1__ Pico ; 

__attribute__((used)) static void DrawLayer(int plane_sh, int *hcache, int cellskip, int maxcells)
{
  struct PicoVideo *pvid=&Pico.video;
  const char shift[4]={5,6,5,7}; // 32,64 or 128 sized tilemaps (2 is invalid)
  struct TileStrip ts;
  int width, height, ymask;
  int vscroll, htab;

  ts.hc=hcache;
  ts.cells=maxcells;

  // Work out the TileStrip to draw

  // Work out the name table size: 32 64 or 128 tiles (0-3)
  width=pvid->reg[16];
  height=(width>>4)&3; width&=3;

  ts.xmask=(1<<shift[width])-1; // X Mask in tiles (0x1f-0x7f)
  ymask=(height<<8)|0xff;       // Y Mask in pixels
  if(width == 1)   ymask&=0x1ff;
  else if(width>1) ymask =0x0ff;

  // Find name table:
  if (plane_sh&1) ts.nametab=(pvid->reg[4]&0x07)<<12; // B
  else            ts.nametab=(pvid->reg[2]&0x38)<< 9; // A

  htab=pvid->reg[13]<<9; // Horizontal scroll table address
  if ( pvid->reg[11]&2)     htab+=DrawScanline<<1; // Offset by line
  if ((pvid->reg[11]&1)==0) htab&=~0xf; // Offset by tile
  htab+=plane_sh&1; // A or B

  // Get horizontal scroll value, will be masked later
  ts.hscroll=Pico.vram[htab&0x7fff];

  if((pvid->reg[12]&6) == 6) {
    // interlace mode 2
    vscroll=Pico.vsram[plane_sh&1]; // Get vertical scroll value

    // Find the line in the name table
    ts.line=(vscroll+(DrawScanline<<1))&((ymask<<1)|1);
    ts.nametab+=(ts.line>>4)<<shift[width];

    DrawStripInterlace(&ts);
  } else if( pvid->reg[11]&4) {
    // shit, we have 2-cell column based vscroll
    // luckily this doesn't happen too often
    ts.line=ymask|(shift[width]<<24); // save some stuff instead of line
    DrawStripVSRam(&ts, plane_sh, cellskip);
  } else {
    vscroll=Pico.vsram[plane_sh&1]; // Get vertical scroll value

    // Find the line in the name table
    ts.line=(vscroll+DrawScanline)&ymask;
    ts.nametab+=(ts.line>>3)<<shift[width];

    DrawStrip(&ts, plane_sh, cellskip);
  }
}