#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int TL; int TLL; int ksl; } ;
typedef  TYPE_1__ YM2413_OPLL_SLOT ;
struct TYPE_9__ {int ksl_base; int block_fnum; int sus; int kcode; int fc; TYPE_1__* SLOT; } ;
typedef  TYPE_2__ YM2413_OPLL_CH ;
typedef  int UINT8 ;
struct TYPE_10__ {int** inst_tab; int rhythm; int* instvol_r; int* fn_tab; TYPE_2__* P_CH; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALC_FCSLOT (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ENV_BITS ; 
 int /*<<< orphan*/  KEY_OFF (TYPE_1__*,int) ; 
 int /*<<< orphan*/  KEY_ON (TYPE_1__*,int) ; 
 size_t SLOT1 ; 
 size_t SLOT2 ; 
 int* ksl_tab ; 
 int /*<<< orphan*/  load_instrument (int,int,int*) ; 
 int /*<<< orphan*/  update_instrument_zero (int) ; 
 TYPE_3__ ym2413 ; 

__attribute__((used)) static void OPLLWriteReg(int r, int v)
{
  YM2413_OPLL_CH *CH;
  YM2413_OPLL_SLOT *SLOT;

  /* adjust bus to 8 bits */
  r &= 0xff;
  v &= 0xff;

  switch(r&0xf0)
  {
    case 0x00:  /* 00-0f:control */
    {
      switch(r&0x0f)
      {
        case 0x00:  /* AM/VIB/EGTYP/KSR/MULTI (modulator) */
        case 0x01:  /* AM/VIB/EGTYP/KSR/MULTI (carrier) */
        case 0x02:  /* Key Scale Level, Total Level (modulator) */
        case 0x03:  /* Key Scale Level, carrier waveform, modulator waveform, Feedback */
        case 0x04:  /* Attack, Decay (modulator) */
        case 0x05:  /* Attack, Decay (carrier) */
        case 0x06:  /* Sustain, Release (modulator) */
        case 0x07:  /* Sustain, Release (carrier) */
        {
          ym2413.inst_tab[0][r] = v;
          update_instrument_zero(r);
          break;
        }

        case 0x0e:  /* x, x, r,bd,sd,tom,tc,hh */
        {
          if(v&0x20)
          {
            /* rhythm OFF to ON */
            if ((ym2413.rhythm&0x20)==0)
            {
              /* Load instrument settings for channel seven(chan=6 since we're zero based). (Bass drum) */
              load_instrument(6, 12, &ym2413.inst_tab[16][0]);

              /* Load instrument settings for channel eight. (High hat and snare drum) */
              load_instrument(7, 14, &ym2413.inst_tab[17][0]);

              CH   = &ym2413.P_CH[7];
              SLOT = &CH->SLOT[SLOT1]; /* modulator envelope is HH */
              SLOT->TL  = ((ym2413.instvol_r[7]>>4)<<2)<<(ENV_BITS-2-7); /* 7 bits TL (bit 6 = always 0) */
              SLOT->TLL = SLOT->TL + (CH->ksl_base>>SLOT->ksl);

              /* Load instrument settings for channel nine. (Tom-tom and top cymbal) */
              load_instrument(8, 16, &ym2413.inst_tab[18][0]);

              CH   = &ym2413.P_CH[8];
              SLOT = &CH->SLOT[SLOT1]; /* modulator envelope is TOM */
              SLOT->TL  = ((ym2413.instvol_r[8]>>4)<<2)<<(ENV_BITS-2-7); /* 7 bits TL (bit 6 = always 0) */
              SLOT->TLL = SLOT->TL + (CH->ksl_base>>SLOT->ksl);
            }

            /* BD key on/off */
            if(v&0x10)
            {
              KEY_ON (&ym2413.P_CH[6].SLOT[SLOT1], 2);
              KEY_ON (&ym2413.P_CH[6].SLOT[SLOT2], 2);
            }
            else
            {
              KEY_OFF(&ym2413.P_CH[6].SLOT[SLOT1],~2);
              KEY_OFF(&ym2413.P_CH[6].SLOT[SLOT2],~2);
            }

            /* HH key on/off */
            if(v&0x01) KEY_ON (&ym2413.P_CH[7].SLOT[SLOT1], 2);
            else       KEY_OFF(&ym2413.P_CH[7].SLOT[SLOT1],~2);

            /* SD key on/off */
            if(v&0x08) KEY_ON (&ym2413.P_CH[7].SLOT[SLOT2], 2);
            else       KEY_OFF(&ym2413.P_CH[7].SLOT[SLOT2],~2);

            /* TOM key on/off */
            if(v&0x04) KEY_ON (&ym2413.P_CH[8].SLOT[SLOT1], 2);
            else       KEY_OFF(&ym2413.P_CH[8].SLOT[SLOT1],~2);

            /* TOP-CY key on/off */
            if(v&0x02) KEY_ON (&ym2413.P_CH[8].SLOT[SLOT2], 2);
            else       KEY_OFF(&ym2413.P_CH[8].SLOT[SLOT2],~2);
          }
          else
          {
            /* rhythm ON to OFF */
            if (ym2413.rhythm&0x20)
            {
              /* Load instrument settings for channel seven(chan=6 since we're zero based).*/
              load_instrument(6, 12, &ym2413.inst_tab[ym2413.instvol_r[6]>>4][0]);

              /* Load instrument settings for channel eight.*/
              load_instrument(7, 14, &ym2413.inst_tab[ym2413.instvol_r[7]>>4][0]);

              /* Load instrument settings for channel nine.*/
              load_instrument(8, 16, &ym2413.inst_tab[ym2413.instvol_r[8]>>4][0]);
            }

            /* BD key off */
            KEY_OFF(&ym2413.P_CH[6].SLOT[SLOT1],~2);
            KEY_OFF(&ym2413.P_CH[6].SLOT[SLOT2],~2);

            /* HH key off */
            KEY_OFF(&ym2413.P_CH[7].SLOT[SLOT1],~2);

            /* SD key off */
            KEY_OFF(&ym2413.P_CH[7].SLOT[SLOT2],~2);

            /* TOM key off */
            KEY_OFF(&ym2413.P_CH[8].SLOT[SLOT1],~2);

            /* TOP-CY off */
            KEY_OFF(&ym2413.P_CH[8].SLOT[SLOT2],~2);
          }

          ym2413.rhythm = v&0x3f;
          break;
        }
      }

      break;
    }

    case 0x10:
    case 0x20:
    {
      int block_fnum;

      int chan = r&0x0f;

      if (chan >= 9)
        chan -= 9;  /* verified on real YM2413 */

      CH = &ym2413.P_CH[chan];

      if(r&0x10)
      {
        /* 10-18: FNUM 0-7 */
        block_fnum = (CH->block_fnum&0x0f00) | v;
      }
      else
      {
        /* 20-28: suson, keyon, block, FNUM 8 */
        block_fnum = ((v&0x0f)<<8) | (CH->block_fnum&0xff);

        if(v&0x10)
        {
          KEY_ON (&CH->SLOT[SLOT1], 1);
          KEY_ON (&CH->SLOT[SLOT2], 1);
        }
        else
        {
          KEY_OFF(&CH->SLOT[SLOT1],~1);
          KEY_OFF(&CH->SLOT[SLOT2],~1);
        }

        CH->sus = v & 0x20;
      }

      /* update */
      if(CH->block_fnum != block_fnum)
      {
        UINT8 block;
        CH->block_fnum = block_fnum;

        /* BLK 2,1,0 bits -> bits 3,2,1 of kcode, FNUM MSB -> kcode LSB */
        CH->kcode    = (block_fnum&0x0f00)>>8;

        CH->ksl_base = ksl_tab[block_fnum>>5];

        block_fnum   = block_fnum * 2;
        block        = (block_fnum&0x1c00) >> 10;
        CH->fc       = ym2413.fn_tab[block_fnum&0x03ff] >> (7-block);

        /* refresh Total Level in both SLOTs of this channel */
        CH->SLOT[SLOT1].TLL = CH->SLOT[SLOT1].TL + (CH->ksl_base>>CH->SLOT[SLOT1].ksl);
        CH->SLOT[SLOT2].TLL = CH->SLOT[SLOT2].TL + (CH->ksl_base>>CH->SLOT[SLOT2].ksl);

        /* refresh frequency counter in both SLOTs of this channel */
        CALC_FCSLOT(CH,&CH->SLOT[SLOT1]);
        CALC_FCSLOT(CH,&CH->SLOT[SLOT2]);
      }

      break;
    }

    case 0x30:  /* inst 4 MSBs, VOL 4 LSBs */
    {
      int chan = r&0x0f;

      if (chan >= 9)
        chan -= 9;  /* verified on real YM2413 */

      CH   = &ym2413.P_CH[chan];
      SLOT = &CH->SLOT[SLOT2]; /* carrier */
      SLOT->TL  = ((v&0x0f)<<2)<<(ENV_BITS-2-7); /* 7 bits TL (bit 6 = always 0) */
      SLOT->TLL = SLOT->TL + (CH->ksl_base>>SLOT->ksl);

      /*check wether we are in rhythm mode and handle instrument/volume register accordingly*/
      if ((chan>=6) && (ym2413.rhythm&0x20))
      {
        /* we're in rhythm mode*/

        if (chan>=7) /* only for channel 7 and 8 (channel 6 is handled in usual way)*/
        {
          SLOT = &CH->SLOT[SLOT1]; /* modulator envelope is HH(chan=7) or TOM(chan=8) */
          SLOT->TL  = ((v>>4)<<2)<<(ENV_BITS-2-7); /* 7 bits TL (bit 6 = always 0) */
          SLOT->TLL = SLOT->TL + (CH->ksl_base>>SLOT->ksl);
        }
      }
      else
      {
        if ((ym2413.instvol_r[chan]&0xf0) != (v&0xf0))
        {
          ym2413.instvol_r[chan] = v;  /* store for later use */
          load_instrument(chan, chan * 2, &ym2413.inst_tab[v>>4][0]);
        }
      }

      break;
    }

    default:
      break;
  }
}