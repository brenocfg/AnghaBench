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
typedef  int uint8 ;
typedef  int uint32 ;
typedef  int int32 ;
typedef  int /*<<< orphan*/  _go32_dpmi_registers ;

/* Variables and functions */
 int LMBuffer ; 
 int ReadPtr ; 
 int SBDMA ; 
 int SBDMA16 ; 
 int SBIRQ ; 
 int SBPort ; 
 int /*<<< orphan*/  UpdateJoyData () ; 
 scalar_t__ WaveBuffer ; 
 int /*<<< orphan*/  _dos_ds ; 
 int /*<<< orphan*/  _farnspokel (int,int) ; 
 int /*<<< orphan*/  _farsetsel (int /*<<< orphan*/ ) ; 
 int format ; 
 int fragsize ; 
 int fragtotal ; 
 int hbusy ; 
 int inportb (int) ; 
 int /*<<< orphan*/  outportb (int,int) ; 
 int soundjoyer ; 
 scalar_t__ soundjoyeron ; 
 scalar_t__ ssilence ; 
 int whichbuf ; 

__attribute__((used)) static void SBIRQHandler(_go32_dpmi_registers *r)
{
        uint32 *src;
	uint32 dest;
	int32 x;


        if(format)
        {
         uint8 status;

         outportb(SBPort+4,0x82);
         status=inportb(SBPort+5);
         if(status&2)
          inportb(SBPort+0x0F);
        }
        else
         inportb(SBPort+0x0E);

        #ifdef OLD
        {
         uint8 status;

         outportb(SBPort+4,0x82);
         status=inportb(SBPort+5);
         if(status&1)
          inportb(SBPort+0x0E);
         else if(status&2)
          inportb(SBPort+0x0F);
         else
          return;               // Mysterious interrupt source!  *eerie music*
        }         
        #endif

        if(hbusy)
        {
         outportb(0x20,0x20);
         if(SBIRQ>=8)
          outportb(0xA0,0x20);
         whichbuf^=1;         
         return;
        }
        hbusy=1;

        {
         /* This code seems to fail on many SB emulators.  Bah.
            SCREW SB EMULATORS. ^_^ */
         uint32 count;
	 uint32 block;
	 uint32 port;
       
         if(format)
          port=((SBDMA16&3)*4)+0xc2;
         else
          port=(SBDMA*2)+1;

         count=inportb(port);
         count|=inportb(port)<<8;

         if(count>=fragsize)
          block=1;
         else
          block=0;
         dest=LMBuffer+((block*fragsize)<<format);

         #ifdef MOO
         dest=LMBuffer+((whichbuf*fragsize)<<format);
         whichbuf^=1;
         #endif
        }

        _farsetsel(_dos_ds);

        src=(uint32 *)(WaveBuffer+(ReadPtr<<format));

	if(ssilence)
	{
	 uint32 sby;
	 if(format) sby=0;	/* 16-bit silence.  */
	 else sby=0x80808080;	/* 8-bit silence.   */

         for(x=(fragsize<<format)>>2;x;x--,dest+=4)
         {
          _farnspokel(dest,sby);
         }
	}
	else
	{
         for(x=(fragsize<<format)>>2;x;x--,dest+=4,src++)
         {
          _farnspokel(dest,*src);
         }
         ReadPtr=(ReadPtr+fragsize)&(fragtotal-1);
	}

        if(soundjoyeron)
        {
         static int coot=0;
         if(!coot)
         {
          UpdateJoyData();
          soundjoyer=1;
         }
         coot=(coot+1)&3;
        }
        hbusy=0;
        outportb(0x20,0x20);
        if(SBIRQ>=8)        
         outportb(0xA0,0x20);
}