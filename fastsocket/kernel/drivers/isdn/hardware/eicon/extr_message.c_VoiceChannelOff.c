#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* adapter; } ;
struct TYPE_7__ {scalar_t__ AdvSignalPLCI; } ;
typedef  TYPE_2__ PLCI ;

/* Variables and functions */
 int /*<<< orphan*/  FTY ; 
 int /*<<< orphan*/  TEL_CTRL ; 
 int /*<<< orphan*/  add_p (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  adv_voice_clear_config (scalar_t__) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  send_req (TYPE_2__*) ; 
 int /*<<< orphan*/  sig_req (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void VoiceChannelOff(PLCI *plci)
{
  dbug(1,dprintf("ExtDevOFF"));
  add_p(plci,FTY,"\x02\x01\x08");             /* B Off */
  sig_req(plci,TEL_CTRL,0);
  send_req(plci);
  if(plci->adapter->AdvSignalPLCI)
  {
    adv_voice_clear_config (plci->adapter->AdvSignalPLCI);
  }
}