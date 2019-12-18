#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* private; scalar_t__ ppDS; scalar_t__ ppbuf; scalar_t__ ppbufsec; } ;
typedef  TYPE_1__ SexyAL_device ;
typedef  TYPE_1__ DSFobby ;

/* Variables and functions */
 int /*<<< orphan*/  IDirectSoundBuffer_Release (scalar_t__) ; 
 int /*<<< orphan*/  IDirectSoundBuffer_Stop (scalar_t__) ; 
 int /*<<< orphan*/  IDirectSound_Release (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  timeEndPeriod (int) ; 

int SexyALI_DSound_Close(SexyAL_device *device)
{
 if(device)
 {
  if(device->private)
  {
   DSFobby *tmp=device->private;
   if(tmp->ppbufsec)
   {
    IDirectSoundBuffer_Stop(tmp->ppbufsec);
    IDirectSoundBuffer_Release(tmp->ppbufsec);
   }
   if(tmp->ppbuf)
   {
    IDirectSoundBuffer_Stop(tmp->ppbuf);
    IDirectSoundBuffer_Release(tmp->ppbuf);
   }
   if(tmp->ppDS)
   {
    IDirectSound_Release(tmp->ppDS);
   }
   free(device->private);
  }
  free(device);
  timeEndPeriod(1);
  return(1);
 }
 return(0);
}