#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ State; } ;
struct TYPE_5__ {int /*<<< orphan*/ * AdvSignalPLCI; int /*<<< orphan*/ * AdvSignalAppl; TYPE_2__* AdvCodecPLCI; scalar_t__ AdvCodecFLAG; } ;
typedef  int /*<<< orphan*/  PLCI ;
typedef  TYPE_1__ DIVA_CAPI_ADAPTER ;

/* Variables and functions */
 scalar_t__ ADVANCED_VOICE_NOSIG ; 
 int /*<<< orphan*/  VoiceChannelOff (TYPE_2__*) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  plci_remove (TYPE_2__*) ; 

__attribute__((used)) static void CodecIdCheck(DIVA_CAPI_ADAPTER *a, PLCI *plci)
{

  dbug(1,dprintf("CodecIdCheck"));

  if(a->AdvSignalPLCI == plci)
  {
    dbug(1,dprintf("PLCI owns codec"));
    VoiceChannelOff(a->AdvCodecPLCI);
    if(a->AdvCodecPLCI->State == ADVANCED_VOICE_NOSIG)
    {
      dbug(1,dprintf("remove temp codec PLCI"));
      plci_remove(a->AdvCodecPLCI);
      a->AdvCodecFLAG  = 0;
      a->AdvCodecPLCI  = NULL;
      a->AdvSignalAppl = NULL;
    }
    a->AdvSignalPLCI = NULL;
  }
}