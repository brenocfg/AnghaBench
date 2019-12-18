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
struct PicoVideo {int* reg; int v_counter; int pending_ints; } ;
struct TYPE_5__ {int pal; int scanline; } ;
struct TYPE_4__ {int nmi_state; } ;
struct TYPE_6__ {TYPE_2__ m; TYPE_1__ ms; struct PicoVideo video; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_INTS ; 
 TYPE_3__ Pico ; 
 int /*<<< orphan*/  PicoFrameStartMode4 () ; 
 int /*<<< orphan*/  PicoLineMode4 (int) ; 
 int* PicoPad ; 
 int PicoSkipFrame ; 
 int /*<<< orphan*/  PsndGetSamplesMS () ; 
 scalar_t__ PsndOut ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  z80_int () ; 
 int /*<<< orphan*/  z80_nmi () ; 
 int z80_run (int) ; 

void PicoFrameMS(void)
{
  struct PicoVideo *pv = &Pico.video;
  int is_pal = Pico.m.pal;
  int lines = is_pal ? 313 : 262;
  int cycles_line = is_pal ? 58020 : 58293; /* (226.6 : 227.7) * 256 */
  int cycles_done = 0, cycles_aim = 0;
  int skip = PicoSkipFrame;
  int lines_vis = 192;
  int hint; // Hint counter
  int nmi;
  int y;

  nmi = (PicoPad[0] >> 7) & 1;
  if (!Pico.ms.nmi_state && nmi)
    z80_nmi();
  Pico.ms.nmi_state = nmi;

  PicoFrameStartMode4();
  hint = pv->reg[0x0a];

  for (y = 0; y < lines; y++)
  {
    pv->v_counter = Pico.m.scanline = y;
    if (y > 218)
      pv->v_counter = y - 6;

    if (y < lines_vis && !skip)
      PicoLineMode4(y);

    if (y <= lines_vis)
    {
      if (--hint < 0)
      {
        hint = pv->reg[0x0a];
        pv->pending_ints |= 2;
        if (pv->reg[0] & 0x10) {
          elprintf(EL_INTS, "hint");
          z80_int();
        }
      }
    }
    else if (y == lines_vis + 1) {
      pv->pending_ints |= 1;
      if (pv->reg[1] & 0x20) {
        elprintf(EL_INTS, "vint");
        z80_int();
      }
    }

    cycles_aim += cycles_line;
    cycles_done += z80_run((cycles_aim - cycles_done) >> 8) << 8;
  }

  if (PsndOut)
    PsndGetSamplesMS();
}