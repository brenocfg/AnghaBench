#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_4__ {size_t mslc; TYPE_1__* slot; } ;
struct TYPE_3__ {int addr_counter; int env_phase; int last_env; } ;

/* Variables and functions */
#define  SCSP_ENV_ATTACK 131 
#define  SCSP_ENV_DECAY 130 
#define  SCSP_ENV_RELEASE 129 
#define  SCSP_ENV_SUSTAIN 128 
 int SCSP_FREQ_LOW_BITS ; 
 TYPE_2__ scsp ; 

__attribute__((used)) static u16 ScspReadMonitor(void)
{
   u8 ca, sgc, eg;

   ca = (scsp.slot[scsp.mslc].addr_counter >> (SCSP_FREQ_LOW_BITS + 12)) & 0xF;

   switch (scsp.slot[scsp.mslc].env_phase) {
      case SCSP_ENV_ATTACK:
         sgc = 0;
         break;
      case SCSP_ENV_DECAY:
         sgc = 1;
         break;
      case SCSP_ENV_SUSTAIN:
         sgc = 2;
         break;
      case SCSP_ENV_RELEASE:
         sgc = 3;
         break;
   }

   eg = 0x1f - (scsp.slot[scsp.mslc].last_env >> 27);

   return (ca << 7) | (sgc << 5) | eg;
}