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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  pointer ;
struct TYPE_4__ {int /*<<< orphan*/  (* SetFetch ) (int,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int mem4b; int mvol; int rbl; int rbp; int mslc; int dmea; int drga; int dmlen; int dmfl; int timasd; int timacnt; int timbsd; int timbcnt; int timcsd; int timccnt; int scieb; int scipd; int scilv0; int scilv1; int scilv2; int mcieb; int mcipd; } ;

/* Variables and functions */
 TYPE_2__* M68K ; 
 int /*<<< orphan*/  SCSPLOG (char*,int,int) ; 
 int /*<<< orphan*/  SoundRam ; 
 TYPE_1__ scsp ; 
 int* scsp_ccr ; 
 int /*<<< orphan*/  scsp_dma () ; 
 int /*<<< orphan*/  scsp_main_interrupt (int) ; 
 int /*<<< orphan*/  scsp_midi_out_send (int) ; 
 int /*<<< orphan*/  scsp_sound_interrupt (int) ; 
 int /*<<< orphan*/  scsp_trigger_sound_interrupt (int) ; 
 int /*<<< orphan*/  scsp_update_monitor () ; 
 int /*<<< orphan*/  stub1 (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
scsp_set_b (u32 a, u8 d)
{
  if ((a != 0x408) && (a != 0x41D))
    {
      SCSPLOG("scsp : reg %.2X = %.2X\n", a & 0x3F, d);
    }

  scsp_ccr[a ^ 3] = d;

  switch (a & 0x3F)
    {
    case 0x00: // MEM4MB/DAC18B
      scsp.mem4b = (d >> 1) & 0x1;
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

    case 0x01: // VER/MVOL
      scsp.mvol = d & 0xF;
      return;

    case 0x02: // RBL(high bit)
      scsp.rbl = (scsp.rbl & 1) + ((d & 1) << 1);
      return;

    case 0x03: // RBL(low bit)/RBP
      scsp.rbl = (scsp.rbl & 2) + ((d >> 7) & 1);
#ifdef USE_NEW_SCSP
      scsp.rbp = (d & 0x7F);
#else
      scsp.rbp = (d & 0x7F) * (4 * 1024 * 2);
#endif
      return;

    case 0x07: // MOBUF
      scsp_midi_out_send(d);
      return;

    case 0x08: // MSLC
      scsp.mslc = (d >> 3) & 0x1F;
      scsp_update_monitor ();
      return;

    case 0x12: // DMEAL(high byte)
      scsp.dmea = (scsp.dmea & 0x700FE) + (d << 8);
      return;

    case 0x13: // DMEAL(low byte)
      scsp.dmea = (scsp.dmea & 0x7FF00) + (d & 0xFE);
      return;

    case 0x14: // DMEAH(high byte)
      scsp.dmea = (scsp.dmea & 0xFFFE) + ((d & 0x70) << 12);
      scsp.drga = (scsp.drga & 0xFE) + ((d & 0xF) << 8);
      return;

    case 0x15: // DMEAH(low byte)
      scsp.drga = (scsp.drga & 0xF00) + (d & 0xFE);
      return;

    case 0x16: // DGATE/DDIR/DEXE/DTLG(upper 4 bits)
      scsp.dmlen = (scsp.dmlen & 0xFE) + ((d & 0xF) << 8);
      if ((scsp.dmfl = d & 0xF0) & 0x10) scsp_dma ();
      return;

    case 0x17: // DTLG(lower byte)
      scsp.dmlen = (scsp.dmlen & 0xF00) + (d & 0xFE);
      return;

    case 0x18: // TACTL
      scsp.timasd = d & 7;
      return;

    case 0x19: // TIMA
      scsp.timacnt = d << 8;
      return;

    case 0x1A: // TBCTL
      scsp.timbsd = d & 7;
      return;

    case 0x1B: // TIMB
      scsp.timbcnt = d << 8;
      return;

    case 0x1C: // TCCTL
      scsp.timcsd = d & 7;
      return;

    case 0x1D: // TIMC
      scsp.timccnt = d << 8;
      return;

    case 0x1E: // SCIEB(high byte)
    {
      int i;
      scsp.scieb = (scsp.scieb & 0xFF) + (d << 8);

      for (i = 0; i < 3; i++)
        {
          if (scsp.scieb & (1 << i) && scsp.scipd & (1 << i))
            scsp_trigger_sound_interrupt ((1 << (i+8)));
        }

      return;
    }
    case 0x1F: // SCIEB(low byte)
    {
      int i;
      scsp.scieb = (scsp.scieb & 0x700) + d;

      for (i = 0; i < 8; i++)
        {
          if (scsp.scieb & (1 << i) && scsp.scipd & (1 << i))
            scsp_trigger_sound_interrupt ((1 << i));
        }
      return;
    }
    case 0x21: // SCIPD(low byte)
      if (d & 0x20) scsp_sound_interrupt (0x20);
      return;

    case 0x22: // SCIRE(high byte)
      scsp.scipd &= ~(d << 8);
      return;

    case 0x23: // SCIRE(low byte)
      scsp.scipd &= ~(u32)d;
      return;

    case 0x25: // SCILV0
      scsp.scilv0 = d;
      return;

    case 0x27: // SCILV1
      scsp.scilv1 = d;
      return;

    case 0x29: // SCILV2
      scsp.scilv2 = d;
      return;

    case 0x2A: // MCIEB(high byte)
      scsp.mcieb = (scsp.mcieb & 0xFF) + (d << 8);
      return;

    case 0x2B: // MCIEB(low byte)
      scsp.mcieb = (scsp.mcieb & 0x700) + d;
      return;

    case 0x2D: // MCIPD(low byte)
      if (d & 0x20)
        scsp_main_interrupt(0x20);
      return;

    case 0x2E: // MCIRE(high byte)
      scsp.mcipd &= ~(d << 8);
      return;

    case 0x2F: // MCIRE(low byte)
      scsp.mcipd &= ~(u32)d;
      return;
    }
}