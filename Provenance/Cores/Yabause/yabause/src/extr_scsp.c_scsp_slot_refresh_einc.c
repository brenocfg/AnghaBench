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
typedef  int u32 ;
struct TYPE_3__ {int fsft; int krs; int /*<<< orphan*/ * rrp; int /*<<< orphan*/  eincr; int /*<<< orphan*/ * srp; int /*<<< orphan*/  eincs; int /*<<< orphan*/ * drp; int /*<<< orphan*/  eincd; int /*<<< orphan*/ * arp; int /*<<< orphan*/  einca; } ;
typedef  TYPE_1__ slot_t ;

/* Variables and functions */

__attribute__((used)) static void
scsp_slot_refresh_einc (slot_t *slot, u32 adsr_bitmask)
{
  if (slot->arp && (adsr_bitmask & 0x1))
    slot->einca = slot->arp[(14 - slot->fsft) >> slot->krs];
  if (slot->drp && (adsr_bitmask & 0x2))
    slot->eincd = slot->drp[(14 - slot->fsft) >> slot->krs];
  if (slot->srp && (adsr_bitmask & 0x4))
    slot->eincs = slot->srp[(14 - slot->fsft) >> slot->krs];
  if (slot->rrp && (adsr_bitmask & 0x8))
    slot->eincr = slot->rrp[(14 - slot->fsft) >> slot->krs];
}