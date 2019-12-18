#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int pcm_mixpos; int* pcm_mixbuf; scalar_t__ pcm_mixbuf_dirty; } ;

/* Variables and functions */
 int POPT_EN_MCD_PCM ; 
 int PicoOpt ; 
 TYPE_1__* Pico_mcd ; 
 int /*<<< orphan*/  SekCyclesDoneS68k () ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcd_pcm_sync (int /*<<< orphan*/ ) ; 

void pcd_pcm_update(int *buf32, int length, int stereo)
{
  int step, *pcm;
  int p = 0;

  pcd_pcm_sync(SekCyclesDoneS68k());

  if (!Pico_mcd->pcm_mixbuf_dirty || !(PicoOpt & POPT_EN_MCD_PCM))
    goto out;

  step = (Pico_mcd->pcm_mixpos << 16) / length;
  pcm = Pico_mcd->pcm_mixbuf;

  if (stereo) {
    while (length-- > 0) {
      *buf32++ += pcm[0];
      *buf32++ += pcm[1];

      p += step;
      pcm += (p >> 16) * 2;
      p &= 0xffff;
    }
  }
  else {
    while (length-- > 0) {
      // mostly unused
      *buf32++ += pcm[0];

      p += step;
      pcm += (p >> 16) * 2;
      p &= 0xffff;
    }
  }

  memset(Pico_mcd->pcm_mixbuf, 0,
    Pico_mcd->pcm_mixpos * 2 * sizeof(Pico_mcd->pcm_mixbuf[0]));

out:
  Pico_mcd->pcm_mixbuf_dirty = 0;
  Pico_mcd->pcm_mixpos = 0;
}