#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ecurp; void* ecnt; int /*<<< orphan*/  enxt; void* ecmp; int /*<<< orphan*/  eincr; int /*<<< orphan*/ * einc; } ;
typedef  TYPE_1__ slot_t ;
struct TYPE_5__ {TYPE_1__* slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSPLOG (char*,int) ; 
 scalar_t__ SCSP_ENV_ATTACK ; 
 void* SCSP_ENV_DE ; 
 scalar_t__ SCSP_ENV_RELEASE ; 
 TYPE_3__ scsp ; 
 int /*<<< orphan*/  scsp_release_next ; 

__attribute__((used)) static void
scsp_slot_keyoff (slot_t *slot)
{
  // key need to be pressed before being released ;)
  if (slot->ecurp != SCSP_ENV_RELEASE)
    {
      SCSPLOG ("key off slot %d\n", slot - &(scsp.slot[0]));

      // if we still are in attack phase at release time, convert attack to decay
      if (slot->ecurp == SCSP_ENV_ATTACK)
        slot->ecnt = SCSP_ENV_DE - slot->ecnt;
      slot->einc = &slot->eincr;
      slot->ecmp = SCSP_ENV_DE;
      slot->ecurp = SCSP_ENV_RELEASE;
      slot->enxt = scsp_release_next;
    }
}