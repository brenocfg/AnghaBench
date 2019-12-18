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
struct TYPE_3__ {unsigned char hardware; unsigned char pal; } ;
struct TYPE_4__ {TYPE_1__ m; scalar_t__ rom; } ;

/* Variables and functions */
 TYPE_2__ Pico ; 
 int PicoAutoRgnOrder ; 
 int PicoRegionOverride ; 
 int strtol (char*,int /*<<< orphan*/ *,int) ; 

void PicoDetectRegion(void)
{
  int support=0, hw=0, i;
  unsigned char pal=0;

  if (PicoRegionOverride)
  {
    support = PicoRegionOverride;
  }
  else
  {
    // Read cartridge region data:
    unsigned short *rd = (unsigned short *)(Pico.rom + 0x1f0);
    int region = (rd[0] << 16) | rd[1];

    for (i = 0; i < 4; i++)
    {
      int c;

      c = region >> (i<<3);
      c &= 0xff;
      if (c <= ' ') continue;

           if (c=='J')  support|=1;
      else if (c=='U')  support|=4;
      else if (c=='E')  support|=8;
      else if (c=='j') {support|=1; break; }
      else if (c=='u') {support|=4; break; }
      else if (c=='e') {support|=8; break; }
      else
      {
        // New style code:
        char s[2]={0,0};
        s[0]=(char)c;
        support|=strtol(s,NULL,16);
      }
    }
  }

  // auto detection order override
  if (PicoAutoRgnOrder) {
         if (((PicoAutoRgnOrder>>0)&0xf) & support) support = (PicoAutoRgnOrder>>0)&0xf;
    else if (((PicoAutoRgnOrder>>4)&0xf) & support) support = (PicoAutoRgnOrder>>4)&0xf;
    else if (((PicoAutoRgnOrder>>8)&0xf) & support) support = (PicoAutoRgnOrder>>8)&0xf;
  }

  // Try to pick the best hardware value for English/50hz:
       if (support&8) { hw=0xc0; pal=1; } // Europe
  else if (support&4)   hw=0x80;          // USA
  else if (support&2) { hw=0x40; pal=1; } // Japan PAL
  else if (support&1)   hw=0x00;          // Japan NTSC
  else hw=0x80; // USA

  Pico.m.hardware=(unsigned char)(hw|0x20); // No disk attached
  Pico.m.pal=pal;
}