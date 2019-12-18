#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int fcnt; int ecurp; int env; } ;
typedef  TYPE_3__ slot_t ;
struct TYPE_10__ {TYPE_2__* slots; } ;
struct TYPE_9__ {int ca; size_t mslc; int sgc; int eg; TYPE_3__* slot; } ;
struct TYPE_6__ {int sample_offset; int envelope; int attenuation; } ;
struct TYPE_7__ {TYPE_1__ state; } ;

/* Variables and functions */
 int SCSP_ENV_HB ; 
 int SCSP_FREQ_LB ; 
 int /*<<< orphan*/  WRITE_THROUGH (int) ; 
 TYPE_5__ new_scsp ; 
 TYPE_4__ scsp ; 

void
scsp_update_monitor(void)
{
#ifdef USE_NEW_SCSP
   scsp.ca = new_scsp.slots[scsp.mslc].state.sample_offset >> 5;
   scsp.sgc = new_scsp.slots[scsp.mslc].state.envelope;
   scsp.eg = new_scsp.slots[scsp.mslc].state.attenuation >> 5;
#else
   slot_t *slot = &scsp.slot[scsp.mslc];
   scsp.ca = ((slot->fcnt >> (SCSP_FREQ_LB + 12)) & 0xF) << 7;
   scsp.sgc = slot->ecurp;
   scsp.eg = 0x1f - (slot->env >> (SCSP_ENV_HB - 5));
#endif
#ifdef PSP
   WRITE_THROUGH(scsp.ca);
   WRITE_THROUGH(scsp.sgc);
   WRITE_THROUGH(scsp.eg);
#endif
}