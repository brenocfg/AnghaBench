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
typedef  int int32 ;
typedef  int int16 ;

/* Variables and functions */
 size_t ReadPtr ; 
 int* WaveBuffer ; 
 size_t WritePtr ; 
 int /*<<< orphan*/  format ; 
 int fragtotal ; 

void WriteSBSound(int32 *Buffer, int Count, int NoBlocking)
{
 int x;

 if(!format)
 {
   for(x=0;x<Count;x++)
   {
    while(WritePtr==ReadPtr)
     if(NoBlocking)
      return;
    WaveBuffer[WritePtr]=(uint8)((Buffer[x])>>8)^128;
    WritePtr=(WritePtr+1)&(fragtotal-1);
   }
 }	
 else // 16 bit
 {
   for(x=0;x<Count;x++)
   {
    while(WritePtr==ReadPtr)
     if(NoBlocking)
      return;
    ((int16 *)WaveBuffer)[WritePtr]=Buffer[x];
    WritePtr=(WritePtr+1)&(fragtotal-1);
   }
 }
}