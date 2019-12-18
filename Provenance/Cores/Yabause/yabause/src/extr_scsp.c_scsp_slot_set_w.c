#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  int u16 ;
struct TYPE_5__ {int key; int sbctl; int ssctl; int lpctl; int pcm8b; int sa; int lsa; int lea; int sr; int dr; int eghold; int ar; int lslnk; int krs; int sl; int rr; int sdir; int swe; int mdl; int mdx; int mdy; int fsft; int finc; int lfoinc; int lfofms; int lfoems; int imxl; int dislr; int disll; int efslr; int efsll; int /*<<< orphan*/  lfoemw; int /*<<< orphan*/  lfofmw; int /*<<< orphan*/  lfocnt; int /*<<< orphan*/  tl; int /*<<< orphan*/ * rrp; int /*<<< orphan*/ * arp; int /*<<< orphan*/ * drp; int /*<<< orphan*/ * srp; int /*<<< orphan*/  ecnt; } ;
typedef  TYPE_1__ slot_t ;
typedef  int s32 ;
struct TYPE_6__ {TYPE_1__* slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSPLOG (char*,size_t,int,int) ; 
 int /*<<< orphan*/  SCSP_ENV_DE ; 
 int SCSP_ENV_DS ; 
 int SCSP_ENV_HB ; 
 int SCSP_ENV_LB ; 
 int SCSP_FREQ_LB ; 
 int SCSP_RAM_MASK ; 
 int /*<<< orphan*/  new_scsp ; 
 TYPE_4__ scsp ; 
 int /*<<< orphan*/ * scsp_attack_rate ; 
 int /*<<< orphan*/ * scsp_decay_rate ; 
 int /*<<< orphan*/ * scsp_isr ; 
 int /*<<< orphan*/  scsp_lfo_noi_e ; 
 int /*<<< orphan*/  scsp_lfo_noi_f ; 
 int /*<<< orphan*/  scsp_lfo_sawt_e ; 
 int /*<<< orphan*/  scsp_lfo_sawt_f ; 
 int /*<<< orphan*/  scsp_lfo_squa_e ; 
 int /*<<< orphan*/  scsp_lfo_squa_f ; 
 int* scsp_lfo_step ; 
 int /*<<< orphan*/  scsp_lfo_tri_e ; 
 int /*<<< orphan*/  scsp_lfo_tri_f ; 
 int /*<<< orphan*/ * scsp_null_rate ; 
 int /*<<< orphan*/  scsp_slot_keyonoff () ; 
 int /*<<< orphan*/  scsp_slot_refresh_einc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  scsp_slot_update_keyon (TYPE_1__*) ; 
 int /*<<< orphan*/  scsp_slot_write_word (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * scsp_tl_table ; 

__attribute__((used)) static void
scsp_slot_set_w (u32 s, s32 a, u16 d)
{
#ifdef USE_NEW_SCSP
  scsp_slot_write_word(&new_scsp, a, d);
#endif
  slot_t *slot = &(scsp.slot[s]);

  SCSPLOG ("slot %d : reg %.2X = %.4X\n", s, a & 0x1E, d);

  *(u16 *)&scsp_isr[a ^ 2] = d;

  switch (a & 0x1E)
    {
    case 0x00: // KYONEX/KYONB/SBCTL/SSCTL/LPCTL/PCM8B/SA(highest 4 bits)
      slot->key = (d >> 11) & 1;
      slot->sbctl = (d >> 9) & 3;
      slot->ssctl = (d >> 7) & 3;
      slot->lpctl = (d >> 5) & 3;

      slot->pcm8b = d & 0x10;
      slot->sa = (slot->sa & 0x0FFFF) | ((d & 0xF) << 16);
      slot->sa &= SCSP_RAM_MASK;

      if (slot->ecnt < SCSP_ENV_DE)
        scsp_slot_update_keyon(slot);

      if (d & 0x1000)
        scsp_slot_keyonoff();
      return;

    case 0x02: // SA(low word)
      slot->sa = (slot->sa & 0xF0000) | d;
      slot->sa &= SCSP_RAM_MASK;

      if (slot->ecnt < SCSP_ENV_DE)
        scsp_slot_update_keyon(slot);
      return;

    case 0x04: // LSA
      slot->lsa = d << SCSP_FREQ_LB;
      return;

    case 0x06: // LEA
      slot->lea = d << SCSP_FREQ_LB;
      return;

    case 0x08: // D2R/D1R/EGHOLD/AR
      slot->sr = (d >> 11) & 0x1F;
      slot->dr = (d >> 6) & 0x1F;
      slot->eghold = d & 0x20;
      slot->ar = d & 0x1F;

      if (slot->sr)
        slot->srp = &scsp_decay_rate[slot->sr << 1];
      else
        slot->srp = &scsp_null_rate[0];

      if (slot->dr)
        slot->drp = &scsp_decay_rate[slot->dr << 1];
      else
        slot->drp = &scsp_null_rate[0];

      if (slot->ar)
        slot->arp = &scsp_attack_rate[slot->ar << 1];
      else
        slot->arp = &scsp_null_rate[0];

      scsp_slot_refresh_einc (slot, 0x1 | 0x2 | 0x4);
      return;

    case 0x0A: // LPSLNK/KRS/DL/RR
      slot->lslnk = (d >> 8) & 0x40;
      slot->krs = (d >> 10) & 0xF;

      if (slot->krs == 0xF)
        slot->krs = 4;
      else
        slot->krs >>= 2;

      slot->sl = ((d & 0x3E0) << SCSP_ENV_LB) + SCSP_ENV_DS; // adjusted for envelope compare (ecmp)
      slot->rr = d & 0x1F;

      if (slot->rr)
        slot->rrp = &scsp_decay_rate[slot->rr << 1];
      else
        slot->rrp = &scsp_null_rate[0];

      scsp_slot_refresh_einc (slot, 0xF);
      return;

    case 0x0C: // STWINH/SDIR
      slot->sdir = (d >> 8) & 2;
      slot->swe = (d >> 8) & 1;
      slot->tl = scsp_tl_table[(d & 0xFF)];
      return;

    case 0x0E: // MDL/MDXSL/MDYSL
      slot->mdl = (d >> 12) & 0xF; // need to adjust for correct shift
      slot->mdx = (d >> 6) & 0x3F;
      slot->mdy = d & 0x3F;
      return;

    case 0x10: // OCT/FNS
      if (d & 0x4000)
        slot->fsft = 23 - ((d >> 11) & 0xF);
      else
        slot->fsft = (((d >> 11) & 7) ^ 7);

      slot->finc = ((0x400 + (d & 0x3FF)) << 7) >> slot->fsft;

      scsp_slot_refresh_einc (slot, 0xF);
      return;

    case 0x12: // LFORE/LFOF/PLFOWS/PLFOS/ALFOWS/ALFOS
      if (d & 0x8000)
        {
          slot->lfoinc = -1;
          return;
        }
      else if (slot->lfoinc == -1)
        {
          slot->lfocnt = 0;
        }

      slot->lfoinc = scsp_lfo_step[(d >> 10) & 0x1F];
      if ((d >> 5) & 7)
        slot->lfofms = ((d >> 5) & 7) + 7;
      else
        slot->lfofms = 31;

      if (d & 7)
        slot->lfoems = ((d & 7) ^ 7) + 4;
      else
        slot->lfoems = 31;

      switch ((d >> 8) & 3)
        {
        case 0:
          slot->lfofmw = scsp_lfo_sawt_f;
          break;

        case 1:
          slot->lfofmw = scsp_lfo_squa_f;
          break;

        case 2:
          slot->lfofmw = scsp_lfo_tri_f;
          break;

        case 3:
          slot->lfofmw = scsp_lfo_noi_f;
          break;
        }

      switch ((d >> 3) & 3)
        {
        case 0:
          slot->lfoemw = scsp_lfo_sawt_e;
          return;

        case 1:
          slot->lfoemw = scsp_lfo_squa_e;
          return;

        case 2:
          slot->lfoemw = scsp_lfo_tri_e;
          return;

        case 3:
          slot->lfoemw = scsp_lfo_noi_e;
        }
      return;

    case 0x14: // ISEL/OMXL
      if (d & 7)
        slot->imxl = ((d & 7) ^ 7) + SCSP_ENV_HB;
      else
        slot->imxl = 31;
      return;

    case 0x16: // DISDL/DIPAN/EFSDL/EFPAN
      if (d & 0xE000)
        {
          // adjusted fr enveloppe calculation
          // some accuracy lose for panning here...
          slot->dislr = slot->disll = (((d >> 13) & 7) ^ 7) + SCSP_ENV_HB;
          if (d & 0x1000)
            {
              // Panning Left
              if ((d & 0xF00) == 0xF00)
                slot->dislr = 31;
              else
                slot->dislr += (d >> 9) & 7;
            }
          else
            {
              // Panning Right
              if ((d & 0xF00) == 0xF00)
                slot->disll = 31;
              else
                slot->disll += (d >> 9) & 7;
            }
        }
      else
        {
          slot->dislr = slot->disll = 31; // muted
        }

      if (d & 0xE0)
        {
          slot->efslr = slot->efsll = (((d >> 5) & 7) ^ 7) + SCSP_ENV_HB;
          if (d & 0x10)
            {
              // Panning Left
              if ((d & 0xF) == 0xF)
                slot->efslr = 31;
              else
                slot->efslr += (d >> 1) & 7;
            }
          else
            {
              // Panning Right
              if ((d & 0xF) == 0xF)
                slot->efsll = 31;
              else
                slot->efsll += (d >> 1) & 7;
            }
        }
      else
        {
          slot->efslr = slot->efsll = 31; // muted
        }
      return;
    }
}