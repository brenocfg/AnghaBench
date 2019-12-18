#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ecurp; size_t sa; int lea; int /*<<< orphan*/  enxt; int /*<<< orphan*/  ecmp; int /*<<< orphan*/  einca; int /*<<< orphan*/ * einc; scalar_t__ env; int /*<<< orphan*/  ecnt; scalar_t__ fcnt; int /*<<< orphan*/ * buf16; int /*<<< orphan*/ * buf8; scalar_t__ pcm8b; int /*<<< orphan*/  lsa; } ;
typedef  TYPE_1__ slot_t ;
typedef  int /*<<< orphan*/  s8 ;
typedef  int /*<<< orphan*/  s16 ;
struct TYPE_7__ {int /*<<< orphan*/  (* GetPC ) () ;} ;
struct TYPE_6__ {int /*<<< orphan*/ * scsp_ram; TYPE_1__* slot; } ;

/* Variables and functions */
 TYPE_4__* M68K ; 
 int /*<<< orphan*/  SCSPLOG (char*,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SCSP_ENV_AE ; 
 int /*<<< orphan*/  SCSP_ENV_AS ; 
 scalar_t__ SCSP_ENV_ATTACK ; 
 scalar_t__ SCSP_ENV_RELEASE ; 
 int SCSP_FREQ_LB ; 
 int SCSP_RAM_MASK ; 
 TYPE_3__ scsp ; 
 int /*<<< orphan*/  scsp_attack_next ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void
scsp_slot_keyon (slot_t *slot)
{
  // key need to be released before being pressed ;)
  if (slot->ecurp == SCSP_ENV_RELEASE)
    {
      SCSPLOG ("key on slot %d. 68K PC = %08X slot->sa = %08X slot->lsa = %08X "
               "slot->lea = %08X\n", slot - &(scsp.slot[0]), M68K->GetPC(),
               slot->sa, slot->lsa, slot->lea >> SCSP_FREQ_LB);

      // set buffer, loop start/end address of the slot
      if (slot->pcm8b)
        {
          slot->buf8 = (s8*) &(scsp.scsp_ram[slot->sa]);
          if ((slot->sa + (slot->lea >> SCSP_FREQ_LB)) > SCSP_RAM_MASK)
            slot->lea = (SCSP_RAM_MASK - slot->sa) << SCSP_FREQ_LB;
        }
      else
        {
          slot->buf16 = (s16*) &(scsp.scsp_ram[slot->sa & ~1]);
          if ((slot->sa + (slot->lea >> (SCSP_FREQ_LB - 1))) > SCSP_RAM_MASK)
            slot->lea = (SCSP_RAM_MASK - slot->sa) << (SCSP_FREQ_LB - 1);
        }

      slot->fcnt = 0;                 // reset frequency counter
      slot->ecnt = SCSP_ENV_AS;       // reset envelope counter (probably wrong,
                                      // should convert decay to attack?)
      slot->env = 0;                  // reset envelope

      slot->einc = &slot->einca;      // envelope counter step is attack step
      slot->ecurp = SCSP_ENV_ATTACK;  // current envelope phase is attack
      slot->ecmp = SCSP_ENV_AE;       // limit reach to next event (Attack End)
      slot->enxt = scsp_attack_next;  // function pointer to next event
    }
}