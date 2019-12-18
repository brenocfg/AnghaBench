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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {void (* sintf ) (u32) ;void (* mintf ) () ;int /*<<< orphan*/ * scsp_ram; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSPLOG (char*,size_t,size_t,size_t) ; 
 scalar_t__ SCSP_ATTACK_R ; 
 scalar_t__ SCSP_DECAY_R ; 
 size_t SCSP_ENV_AE ; 
 size_t SCSP_ENV_LB ; 
 size_t SCSP_ENV_LEN ; 
 scalar_t__ SCSP_ENV_MASK ; 
 double SCSP_FREQ ; 
 int SCSP_LFO_LB ; 
 size_t SCSP_LFO_LEN ; 
 size_t SCSP_LFO_MASK ; 
 double pow (int,double) ; 
 size_t rand () ; 
 TYPE_1__ scsp ; 
 size_t* scsp_attack_rate ; 
 int /*<<< orphan*/ * scsp_ccr ; 
 int /*<<< orphan*/ * scsp_dcr ; 
 size_t* scsp_decay_rate ; 
 scalar_t__* scsp_env_table ; 
 int /*<<< orphan*/ * scsp_isr ; 
 size_t* scsp_lfo_noi_e ; 
 size_t* scsp_lfo_noi_f ; 
 size_t* scsp_lfo_sawt_e ; 
 size_t* scsp_lfo_sawt_f ; 
 size_t* scsp_lfo_squa_e ; 
 int* scsp_lfo_squa_f ; 
 void** scsp_lfo_step ; 
 size_t* scsp_lfo_tri_e ; 
 size_t* scsp_lfo_tri_f ; 
 scalar_t__* scsp_null_rate ; 
 int /*<<< orphan*/ * scsp_reg ; 
 int /*<<< orphan*/  scsp_reset () ; 
 void* scsp_round (double) ; 
 int /*<<< orphan*/  scsp_shutdown () ; 
 void** scsp_tl_table ; 

void
scsp_init (u8 *scsp_ram, void (*sint_hand)(u32), void (*mint_hand)(void))
{
  u32 i, j;
  double x;

  scsp_shutdown ();

  scsp_isr = &scsp_reg[0x0000];
  scsp_ccr = &scsp_reg[0x0400];
  scsp_dcr = &scsp_reg[0x0700];

  scsp.scsp_ram = scsp_ram;
  scsp.sintf = sint_hand;
  scsp.mintf = mint_hand;

  for (i = 0; i < SCSP_ENV_LEN; i++)
    {
      // Attack Curve (x^7 ?)
      x = pow (((double)(SCSP_ENV_MASK - i) / (double)SCSP_ENV_LEN), 7);
      x *= (double)SCSP_ENV_LEN;
      scsp_env_table[i] = SCSP_ENV_MASK - (s32)x;

      // Decay curve (x = linear)
      x = pow (((double)i / (double)SCSP_ENV_LEN), 1);
      x *= (double)SCSP_ENV_LEN;
      scsp_env_table[i + SCSP_ENV_LEN] = SCSP_ENV_MASK - (s32)x;
    }

  for (i = 0, j = 0; i < 32; i++)
    {
      j += 1 << (i >> 2);

      // lfo freq
      x = (SCSP_FREQ / 256.0) / (double)j;

      // converting lfo freq in lfo step
      scsp_lfo_step[31 - i] = scsp_round(x * ((double)SCSP_LFO_LEN /
                                              (double)SCSP_FREQ) *
                                         (double)(1 << SCSP_LFO_LB));
    }

  // Calculate LFO (modulation) values
  for (i = 0; i < SCSP_LFO_LEN; i++)
    {
      // Envelope modulation
      scsp_lfo_sawt_e[i] = SCSP_LFO_MASK - i;

      if (i < (SCSP_LFO_LEN / 2))
        scsp_lfo_squa_e[i] = SCSP_LFO_MASK;
      else
        scsp_lfo_squa_e[i] = 0;

      if (i < (SCSP_LFO_LEN / 2))
        scsp_lfo_tri_e[i] = SCSP_LFO_MASK - (i * 2);
      else
        scsp_lfo_tri_e[i] = (i - (SCSP_LFO_LEN / 2)) * 2;

      scsp_lfo_noi_e[i] = rand() & SCSP_LFO_MASK;

      // Frequency modulation
      scsp_lfo_sawt_f[(i + 512) & SCSP_LFO_MASK] = i - (SCSP_LFO_LEN / 2);

      if (i < (SCSP_LFO_LEN / 2))
        scsp_lfo_squa_f[i] = SCSP_LFO_MASK - (SCSP_LFO_LEN / 2) - 128;
      else
        scsp_lfo_squa_f[i] = 0 - (SCSP_LFO_LEN / 2) + 128;

      if (i < (SCSP_LFO_LEN / 2))
        scsp_lfo_tri_f[(i + 768) & SCSP_LFO_MASK] = (i * 2) -
                                                    (SCSP_LFO_LEN / 2);
      else
        scsp_lfo_tri_f[(i + 768) & SCSP_LFO_MASK] =
          (SCSP_LFO_MASK - ((i - (SCSP_LFO_LEN / 2)) * 2)) -
          (SCSP_LFO_LEN / 2) + 1;

      scsp_lfo_noi_f[i] = scsp_lfo_noi_e[i] - (SCSP_LFO_LEN / 2);
    }

  for(i = 0; i < 4; i++)
    {
      scsp_attack_rate[i] = 0;
      scsp_decay_rate[i] = 0;
    }

  for(i = 0; i < 60; i++)
    {
      x = 1.0 + ((i & 3) * 0.25);                  // bits 0-1 : x1.00, x1.25, x1.50, x1.75
      x *= (double)(1 << ((i >> 2)));              // bits 2-5 : shift bits (x2^0 - x2^15)
      x *= (double)(SCSP_ENV_LEN << SCSP_ENV_LB);  // adjust for table scsp_env_table

      scsp_attack_rate[i + 4] = scsp_round(x / (double)SCSP_ATTACK_R);
      scsp_decay_rate[i + 4] = scsp_round(x / (double)SCSP_DECAY_R);

      if (scsp_attack_rate[i + 4] == 0) scsp_attack_rate[i + 4] = 1;
      if (scsp_decay_rate[i + 4] == 0) scsp_decay_rate[i + 4] = 1;
    }

  scsp_attack_rate[63] = SCSP_ENV_AE;
  scsp_decay_rate[61] = scsp_decay_rate[60];
  scsp_decay_rate[62] = scsp_decay_rate[60];
  scsp_decay_rate[63] = scsp_decay_rate[60];

  for(i = 64; i < 96; i++)
    {
      scsp_attack_rate[i] = scsp_attack_rate[63];
      scsp_decay_rate[i] = scsp_decay_rate[63];
      scsp_null_rate[i - 64] = 0;
    }

  for(i = 0; i < 96; i++)
    {
      SCSPLOG ("attack rate[%d] = %.8X -> %.8X\n", i, scsp_attack_rate[i],
               scsp_attack_rate[i] >> SCSP_ENV_LB);
      SCSPLOG ("decay rate[%d] = %.8X -> %.8X\n", i, scsp_decay_rate[i],
               scsp_decay_rate[i] >> SCSP_ENV_LB);
    }

  for(i = 0; i < 256; i++)
    scsp_tl_table[i] = scsp_round(pow(10, ((double)i * -0.3762) / 20) * 1024.0);

  scsp_reset();
}