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
typedef  int int32 ;

/* Variables and functions */
 int /*<<< orphan*/  DOSMemSet (int,int,int) ; 
 int LMBuffer ; 
 int /*<<< orphan*/  LMSelector ; 
 int __dpmi_allocate_dos_memory (int,int /*<<< orphan*/ *) ; 
 int format ; 
 int fragsize ; 

__attribute__((used)) static int MakeDMABuffer(void)
{
 uint32 size;
 int32 tmp;

 size=fragsize*2;       /* Two buffers in the DMA buffer. */
 size<<=format;         /* Twice the size for 16-bit than for 8-bit. */

 size<<=1;              /* Double the size in case the first 2 buffers
                           cross a 64KB or 128KB page boundary.
                        */
 size=(size+15)>>4;     /* Convert to paragraphs */

 if((tmp=__dpmi_allocate_dos_memory(size,&LMSelector))<0)
  return(0);

 LMBuffer=tmp<<=4;

 if(format)   /* Check for and fix 128KB page boundary crossing. */
 {
  if((LMBuffer&0x20000) != ((LMBuffer+fragsize*2*2-1)&0x20000))
   LMBuffer+=fragsize*2*2;
 }
 else   /* Check for and fix 64KB page boundary crossing. */
 {
  if((LMBuffer&0x10000) != ((LMBuffer+fragsize*2-1)&0x10000))
   LMBuffer+=fragsize*2;
 }

 DOSMemSet(LMBuffer, format?0:128, (fragsize*2)<<format);

 return(1);
}