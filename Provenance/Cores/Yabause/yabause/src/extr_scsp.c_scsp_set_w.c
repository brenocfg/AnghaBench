#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  pointer ;
struct TYPE_4__ {int /*<<< orphan*/  (* SetFetch ) (int,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int mem4b; int mvol; int rbl; int rbp; int mslc; int dmea; int drga; int dmlen; int dmfl; int timasd; int timacnt; int timbsd; int timbcnt; int timcsd; int timccnt; int scieb; int scipd; int scilv0; int scilv1; int scilv2; int mcieb; int mcipd; } ;

/* Variables and functions */
 TYPE_2__* M68K ; 
 int /*<<< orphan*/  SCSPLOG (char*,int,int) ; 
 int /*<<< orphan*/  SoundRam ; 
 TYPE_1__ scsp ; 
 int /*<<< orphan*/ * scsp_ccr ; 
 int /*<<< orphan*/  scsp_dma () ; 
 int /*<<< orphan*/  scsp_main_interrupt (int) ; 
 int /*<<< orphan*/  scsp_midi_out_send (int) ; 
 int /*<<< orphan*/  scsp_sound_interrupt (int) ; 
 int /*<<< orphan*/  scsp_trigger_main_interrupt (int) ; 
 int /*<<< orphan*/  scsp_trigger_sound_interrupt (int) ; 
 int /*<<< orphan*/  scsp_update_monitor () ; 
 int /*<<< orphan*/  stub1 (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
scsp_set_w (u32 a, u16 d)
{
  if ((a != 0x418) && (a != 0x41A) && (a != 0x422))
    {
      SCSPLOG("scsp : reg %.2X = %.4X\n", a & 0x3E, d);
    }

  *(u16 *)&scsp_ccr[a ^ 2] = d;

  switch (a & 0x3E)
    {
    case 0x00: // MEM4MB/DAC18B/VER/MVOL
      scsp.mem4b = (d >> 9) & 0x1;
      scsp.mvol = d & 0xF;
      if (scsp.mem4b)
        {
          M68K->SetFetch(0x000000, 0x080000, (pointer)SoundRam);
        }
      else
        {
          M68K->SetFetch(0x000000, 0x040000, (pointer)SoundRam);
          M68K->SetFetch(0x040000, 0x080000, (pointer)SoundRam);
          M68K->SetFetch(0x080000, 0x0C0000, (pointer)SoundRam);
          M68K->SetFetch(0x0C0000, 0x100000, (pointer)SoundRam);
        }
      return;

    case 0x02: // RBL/RBP
      scsp.rbl = (d >> 7) & 3;
#ifdef USE_NEW_SCSP
      scsp.rbp = (d & 0x7F);
#else
      scsp.rbp = (d & 0x7F) * (4 * 1024 * 2);
#endif
      return;

    case 0x06: // MOBUF
      scsp_midi_out_send(d & 0xFF);
      return;

    case 0x08: // MSLC
      scsp.mslc = (d >> 11) & 0x1F;
      scsp_update_monitor();
      return;

    case 0x12: // DMEAL
      scsp.dmea = (scsp.dmea & 0x70000) + (d & 0xFFFE);
      return;

    case 0x14: // DMEAH/DRGA
      scsp.dmea = (scsp.dmea & 0xFFFE) + ((d & 0x7000) << 4);
      scsp.drga = d & 0xFFE;
      return;

    case 0x16: // DGATE/DDIR/DEXE/DTLG
      scsp.dmlen = d & 0xFFE;
      if ((scsp.dmfl = ((d >> 8) & 0xF0)) & 0x10) scsp_dma ();
      return;

    case 0x18: // TACTL/TIMA
      scsp.timasd = (d >> 8) & 7;
      scsp.timacnt = (d & 0xFF) << 8;
      return;

    case 0x1A: // TBCTL/TIMB
      scsp.timbsd = (d >> 8) & 7;
      scsp.timbcnt = (d & 0xFF) << 8;
      return;

    case 0x1C: // TCCTL/TIMC
      scsp.timcsd = (d >> 8) & 7;
      scsp.timccnt = (d & 0xFF) << 8;
      return;

    case 0x1E: // SCIEB
    {
      int i;
      scsp.scieb = d;
      for (i = 0; i < 11; i++)
        {
          if (scsp.scieb & (1 << i) && scsp.scipd & (1 << i))
            scsp_trigger_sound_interrupt ((1 << i));
        }
      return;
    }
    case 0x20: // SCIPD
      if (d & 0x20) scsp_sound_interrupt (0x20);
      return;

    case 0x22: // SCIRE
      scsp.scipd &= ~d;
      return;

    case 0x24: // SCILV0
      scsp.scilv0 = d;
      return;

    case 0x26: // SCILV1
      scsp.scilv1 = d;
      return;

    case 0x28: // SCILV2
      scsp.scilv2 = d;
      return;

    case 0x2A: // MCIEB
    {
      int i;
      scsp.mcieb = d;
      for (i = 0; i < 11; i++)
        {
          if (scsp.mcieb & (1 << i) && scsp.mcipd & (1 << i))
            scsp_trigger_main_interrupt ((1 << i));
        }
      return;
    }

    case 0x2C: // MCIPD
      if (d & 0x20) scsp_main_interrupt (0x20);
      return;

    case 0x2E: // MCIRE
      scsp.mcipd &= ~d;
      return;
    }
}