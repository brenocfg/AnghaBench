#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  slot_t ;
struct TYPE_5__ {int /*<<< orphan*/  enxt; int /*<<< orphan*/  ecurp; int /*<<< orphan*/  ecmp; int /*<<< orphan*/  einca; int /*<<< orphan*/ * einc; int /*<<< orphan*/  ecnt; scalar_t__ fcnt; } ;
struct TYPE_4__ {int /*<<< orphan*/ * slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSP_ENV_AE ; 
 int /*<<< orphan*/  SCSP_ENV_AS ; 
 int /*<<< orphan*/  SCSP_ENV_ATTACK ; 
 TYPE_2__ debugslot ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__ scsp ; 
 int /*<<< orphan*/  scsp_attack_next ; 

void
ScspSlotResetDebug(u8 slotnum)
{
  memcpy (&debugslot, &scsp.slot[slotnum], sizeof(slot_t));

  // Clear out the phase counter, etc.
  debugslot.fcnt = 0;
  debugslot.ecnt = SCSP_ENV_AS;
  debugslot.einc = &debugslot.einca;
  debugslot.ecmp = SCSP_ENV_AE;
  debugslot.ecurp = SCSP_ENV_ATTACK;
  debugslot.enxt = scsp_attack_next;
}