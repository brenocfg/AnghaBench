#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  enxt; int /*<<< orphan*/  ecurp; int /*<<< orphan*/  sl; int /*<<< orphan*/  ecmp; int /*<<< orphan*/  eincd; int /*<<< orphan*/ * einc; int /*<<< orphan*/  ecnt; } ;
typedef  TYPE_1__ slot_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCSP_ENV_DECAY ; 
 int /*<<< orphan*/  SCSP_ENV_DS ; 
 int /*<<< orphan*/  scsp_decay_next ; 

__attribute__((used)) static void
scsp_attack_next (slot_t *slot)
{
  // end of attack happened, update to process the next phase...

  slot->ecnt = SCSP_ENV_DS;
  slot->einc = &slot->eincd;
  slot->ecmp = slot->sl;
  slot->ecurp = SCSP_ENV_DECAY;
  slot->enxt = scsp_decay_next;
}