#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int int32_t ;
struct TYPE_6__ {int BufHowMuch; int DSBufferSize; int ToWritePos; int /*<<< orphan*/  ppbufw; } ;
struct TYPE_5__ {TYPE_2__* private; } ;
typedef  TYPE_1__ SexyAL_device ;
typedef  int DWORD ;
typedef  TYPE_2__ DSFobby ;

/* Variables and functions */
 int /*<<< orphan*/  CheckStatus (TYPE_2__*) ; 
 scalar_t__ DS_OK ; 
 scalar_t__ IDirectSoundBuffer_GetCurrentPosition (int /*<<< orphan*/ ,int*,int*) ; 

uint32_t SexyALI_DSound_RawCanWrite(SexyAL_device *device)
{
 DSFobby *tmp=device->private;
 DWORD CurWritePos,CurPlayPos=0;
 CheckStatus(tmp);

 CurWritePos=0;

 if(IDirectSoundBuffer_GetCurrentPosition(tmp->ppbufw,&CurPlayPos,&CurWritePos)==DS_OK)
 {
   //FCEU_DispMessage("%d",CurWritePos-CurPlayPos);
 }
 CurWritePos=(CurPlayPos+tmp->BufHowMuch)%tmp->DSBufferSize;

 /*  If the current write pos is >= half the buffer size less than the to write pos,
     assume DirectSound has wrapped around.
 */

 if(((int32_t)tmp->ToWritePos-(int32_t)CurWritePos) >= (tmp->DSBufferSize/2))
 {
  CurWritePos+=tmp->DSBufferSize;
  //printf("Fixit: %d,%d,%d\n",tmp->ToWritePos,CurWritePos,CurWritePos-tmp->DSBufferSize);
 }
 if(tmp->ToWritePos<CurWritePos)
 {
  int32_t howmuch=(int32_t)CurWritePos-(int32_t)tmp->ToWritePos;
  if(howmuch > tmp->BufHowMuch)      /* Oopsie.  Severe buffer overflow... */
  {
   tmp->ToWritePos=CurWritePos%tmp->DSBufferSize;
   //IDirectSoundBuffer_Stop(tmp->ppbufsec);
   //IDirectSoundBuffer_SetCurrentPosition(tmp->ppbufsec,tmp->ToWritePos);
   //puts("Oops");
   //fflush(stdout);
   //return(0);
  }
  return(CurWritePos-tmp->ToWritePos);
 }
 else
  return(0);
}