#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  size_t s32 ;
typedef  int /*<<< orphan*/  s16 ;
struct TYPE_6__ {int (* GetAudioSpace ) () ;int /*<<< orphan*/  (* UpdateAudio ) (int*,int*,int) ;} ;
struct TYPE_5__ {int scsptiming2; int scsptiming1; } ;
struct TYPE_4__ {int* data32; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_AviSoundUpdate (scalar_t__,int) ; 
 int /*<<< orphan*/  SCSPLOG (char*,long) ; 
 TYPE_3__* SNDCore ; 
 int /*<<< orphan*/  ScspConvert32uto16s (size_t*,size_t*,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* ScspInternalVars ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsp_update (size_t*,size_t*,int) ; 
 int /*<<< orphan*/  scsp_update_monitor () ; 
 int /*<<< orphan*/  scsp_update_timer (int) ; 
 TYPE_1__* scspchannel ; 
 scalar_t__ scspframeaccurate ; 
 int scsplines ; 
 int scspsoundbufsize ; 
 int scspsoundgenpos ; 
 int scspsoundlen ; 
 int scspsoundoutleft ; 
 scalar_t__ stereodata16 ; 
 int stub1 () ; 
 int /*<<< orphan*/  stub2 (int*,int*,int) ; 
 int stub3 () ; 
 int /*<<< orphan*/  stub4 (int*,int*,int) ; 

void
ScspExec ()
{
  u32 audiosize;

  ScspInternalVars->scsptiming2 +=
    ((scspsoundlen << 16) + scsplines / 2) / scsplines;
  scsp_update_timer (ScspInternalVars->scsptiming2 >> 16); // Pass integer part
  ScspInternalVars->scsptiming2 &= 0xFFFF; // Keep fractional part
  ScspInternalVars->scsptiming1++;

  if (ScspInternalVars->scsptiming1 >= scsplines)
    {
      s32 *bufL, *bufR;

      ScspInternalVars->scsptiming1 -= scsplines;
      ScspInternalVars->scsptiming2 = 0;

      if (scspframeaccurate)
        {
          // Update sound buffers
          if (scspsoundgenpos + scspsoundlen > scspsoundbufsize)
            scspsoundgenpos = 0;

          if (scspsoundoutleft + scspsoundlen > scspsoundbufsize)
            {
              u32 overrun = (scspsoundoutleft + scspsoundlen) -
                            scspsoundbufsize;
              SCSPLOG ("WARNING: Sound buffer overrun, %lu samples\n",
                       (long)overrun);
              scspsoundoutleft -= overrun;
            }

          bufL = (s32 *)&scspchannel[0].data32[scspsoundgenpos];
          bufR = (s32 *)&scspchannel[1].data32[scspsoundgenpos];
          memset (bufL, 0, sizeof(u32) * scspsoundlen);
          memset (bufR, 0, sizeof(u32) * scspsoundlen);
          scsp_update (bufL, bufR, scspsoundlen);
          scspsoundgenpos += scspsoundlen;
          scspsoundoutleft += scspsoundlen;
        }
    }

  if (scspframeaccurate)
    {
      while (scspsoundoutleft > 0 &&
             (audiosize = SNDCore->GetAudioSpace ()) > 0)
        {
          s32 outstart = (s32)scspsoundgenpos - (s32)scspsoundoutleft;

          if (outstart < 0)
            outstart += scspsoundbufsize;
          if (audiosize > scspsoundoutleft)
            audiosize = scspsoundoutleft;
          if (audiosize > scspsoundbufsize - outstart)
            audiosize = scspsoundbufsize - outstart;

          SNDCore->UpdateAudio (&scspchannel[0].data32[outstart],
                                &scspchannel[1].data32[outstart], audiosize);
          scspsoundoutleft -= audiosize;

#if 0
          ScspConvert32uto16s (&scspchannel[0].data32[outstart],
                               &scspchannel[1].data32[outstart],
                               (s16 *)stereodata16, audiosize);
          DRV_AviSoundUpdate(stereodata16, audiosize);
#endif
        }
    }
  else
    {
      if ((audiosize = SNDCore->GetAudioSpace ()))
        {
          if (audiosize > scspsoundlen)
            audiosize = scspsoundlen;
          memset(scspchannel[0].data32, 0, sizeof(u32) * audiosize);
          memset(scspchannel[1].data32, 0, sizeof(u32) * audiosize);

          scsp_update ((s32 *)scspchannel[0].data32,
                       (s32 *)scspchannel[1].data32, audiosize);
          SNDCore->UpdateAudio (scspchannel[0].data32,
                                (u32 *)scspchannel[1].data32, audiosize);

#if 0
          ScspConvert32uto16s ((s32 *)scspchannel[0].data32,
                               (s32 *)scspchannel[1].data32,
                               (s16 *)stereodata16, audiosize);
          DRV_AviSoundUpdate (stereodata16, audiosize);
#endif
        }
    }  // if (scspframeaccurate)

  scsp_update_monitor ();
}