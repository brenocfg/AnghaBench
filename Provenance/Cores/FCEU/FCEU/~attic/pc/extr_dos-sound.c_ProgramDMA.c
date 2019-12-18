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
 int LMBuffer ; 
 int SBDMA ; 
 int SBDMA16 ; 
 int format ; 
 int fragsize ; 
 int /*<<< orphan*/  outportb (int,int) ; 

__attribute__((used)) static void ProgramDMA(void)
{
 static int PPorts[8]={0x87,0x83,0x81,0x82,0,0x8b,0x89,0x8a};
 uint32 tmp;

 if(format)
 {
  outportb(0xd4,(SBDMA16&0x3)|0x4);
  outportb(0xd8,0x0);
  outportb(0xd6,(SBDMA16&0x3)|0x58);
  tmp=((SBDMA16&3)<<2)+0xC2;
 }
 else
 {
  outportb(0xA,SBDMA|0x4);
  outportb(0xC,0x0);
  outportb(0xB,SBDMA|0x58);
  tmp=(SBDMA<<1)+1;
 }

 /* Size of entire buffer. */
 outportb(tmp,(fragsize*2-1));
 outportb(tmp,(fragsize*2-1)>>8);

 /* Page of buffer. */
 outportb(PPorts[format?SBDMA16:SBDMA],LMBuffer>>16);

 /* Offset of buffer within page. */
 if(format)
  tmp=((SBDMA16&3)<<2)+0xc0;
 else
  tmp=SBDMA<<1;

 outportb(tmp,(LMBuffer>>format));
 outportb(tmp,(LMBuffer>>(8+format)));
}