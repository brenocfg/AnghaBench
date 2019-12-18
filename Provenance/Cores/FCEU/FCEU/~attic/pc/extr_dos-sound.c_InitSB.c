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
 int DSPV ; 
 int /*<<< orphan*/  GetBLASTER () ; 
 int GetDSPVersion () ; 
 int IVector ; 
 int /*<<< orphan*/  KillDMABuffer () ; 
 int /*<<< orphan*/  MakeDMABuffer () ; 
 int PICMask ; 
 int /*<<< orphan*/  ProgramDMA () ; 
 scalar_t__ ReadPtr ; 
 int /*<<< orphan*/  ResetDSP () ; 
 int SBDMA ; 
 int SBDMA16 ; 
 int SBIRQ ; 
 int /*<<< orphan*/  SetVectors () ; 
 int /*<<< orphan*/  WaveBuffer ; 
 int /*<<< orphan*/  WriteDSP (int) ; 
 scalar_t__ WritePtr ; 
 int format ; 
 int frags ; 
 int fragsize ; 
 int fragtotal ; 
 int hbusy ; 
 int hsmode ; 
 int inportb (int) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  outportb (int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int whichbuf ; 

int InitSB(int Rate, int bittage)
{
 hsmode=hbusy=0;
 whichbuf=1;
 puts("Initializing Sound Blaster...");

 format=bittage?1:0;
 frags=8;

 if(Rate<=11025)
  fragsize=1<<5;
 else if(Rate<=22050)
  fragsize=1<<6;
 else
  fragsize=1<<7;

 fragtotal=frags*fragsize;
 WaveBuffer=malloc(fragtotal<<format);

 if(format)
  memset(WaveBuffer,0,fragtotal*2);
 else
  memset(WaveBuffer,128,fragtotal);

 WritePtr=ReadPtr=0;

 if((Rate<8192) || (Rate>65535))
 {
  printf(" Unsupported playback rate: %d samples per second\n",Rate);
  return(0);
 }

 if(!GetBLASTER())
  return(0);
 
 /* Disable IRQ line in PIC0 or PIC1 */
 if(SBIRQ>7)
 {
  PICMask=inportb(0xA1);
  outportb(0xA1,PICMask|(1<<(SBIRQ&7)));
 }
 else
 {
  PICMask=inportb(0x21);
  outportb(0x21,PICMask|(1<<SBIRQ));
 }
 if(!ResetDSP())
 {
  puts(" Error resetting the DSP.");
  return(0);
 }
 
 if(!(DSPV=GetDSPVersion()))
 {
  puts(" Error getting the DSP version.");
  return(0);
 }

 printf(" DSP Version: %d.%d\n",DSPV>>8,DSPV&0xFF);
 if(DSPV<0x201)
 {
  printf(" DSP version number is too low.\n");
  return(0);
 }

 if(DSPV<0x400)
  format=0;
 if(!MakeDMABuffer())
 {
  puts(" Error creating low-memory DMA buffer.");
  return(0);
 }

 if(SBIRQ>7) IVector=SBIRQ+0x68;
 else IVector=SBIRQ+0x8;

 if(!SetVectors())
 {
  puts(" Error setting interrupt vectors.");
  KillDMABuffer();
  return(0);
 }

 /* Reenable IRQ line. */
 if(SBIRQ>7)
  outportb(0xA1,PICMask&(~(1<<(SBIRQ&7))));
 else
  outportb(0x21,PICMask&(~(1<<SBIRQ)));

 ProgramDMA();

 /* Note that the speaker must always be turned on before the mode transfer
    byte is sent to the DSP if we're going into high-speed mode, since
    a real Sound Blaster(at least my SBPro) won't accept DSP commands(except
    for the reset "command") after it goes into high-speed mode.
 */
 WriteDSP(0xD1);                 // Turn on DAC speaker

 if(DSPV>=0x400)
 {
  WriteDSP(0x41);                // Set sampling rate
  WriteDSP(Rate>>8);             // High byte
  WriteDSP(Rate&0xFF);           // Low byte
  if(!format)
  {
   WriteDSP(0xC6);                // 8-bit output
   WriteDSP(0x00);                // 8-bit mono unsigned PCM
  }
  else
  {
   WriteDSP(0xB6);                // 16-bit output
   WriteDSP(0x10);                // 16-bit mono signed PCM
  }
  WriteDSP((fragsize-1)&0xFF);// Low byte of size
  WriteDSP((fragsize-1)>>8);  // High byte of size
 }
 else
 {
  int tc,command;
  if(Rate>22050)
  {
   tc=(65536-(256000000/Rate))>>8;
   Rate=256000000/(65536-(tc<<8));
   command=0x90;                  // High-speed auto-initialize DMA mode transfer
   hsmode=1;
  }
  else
  {
   tc=256-(1000000/Rate);
   Rate=1000000/(256-tc);
   command=0x1c;                  // Auto-initialize DMA mode transfer
  }
  WriteDSP(0x40);       // Set DSP time constant
  WriteDSP(tc);         // time constant
  WriteDSP(0x48);       // Set DSP block transfer size
  WriteDSP((fragsize-1)&0xFF);
  WriteDSP((fragsize-1)>>8);

  WriteDSP(command);
 }

 /* Enable DMA */
 if(format)
  outportb(0xd4,SBDMA16&3);
 else
  outportb(0xa,SBDMA);

 printf(" %d hz, %d-bit\n",Rate,8<<format);
 return(Rate);
}