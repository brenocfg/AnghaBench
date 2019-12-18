#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int ssize_t ;
struct TYPE_5__ {TYPE_1__* wavebufs; } ;
typedef  TYPE_2__ libnx_audren_t ;
struct TYPE_4__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ AudioDriverWaveBufState_Done ; 
 scalar_t__ AudioDriverWaveBufState_Free ; 
 unsigned int BUFFER_COUNT ; 

__attribute__((used)) static ssize_t libnx_audren_audio_get_free_wavebuf_idx(libnx_audren_t* aud)
{
   unsigned i;

   for (i = 0; i < BUFFER_COUNT; i++)
   {
      if (aud->wavebufs[i].state == AudioDriverWaveBufState_Free
         || aud->wavebufs[i].state == AudioDriverWaveBufState_Done)
      {
         return i;
      }
   }

   return -1;
}