#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t word ;
typedef  int /*<<< orphan*/  dword ;
typedef  char byte ;
struct TYPE_10__ {int Id; } ;
struct TYPE_9__ {TYPE_1__* adapter; } ;
struct TYPE_8__ {size_t* Info_Mask; } ;
typedef  TYPE_2__ PLCI ;
typedef  TYPE_3__ APPL ;

/* Variables and functions */
 size_t MAXPARMSIDS ; 
 int /*<<< orphan*/  _INFO_I ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 
 int /*<<< orphan*/  mixer_set_bchannel_id (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  sendf (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,char*) ; 

__attribute__((used)) static void SendSetupInfo(APPL   * appl, PLCI   * plci, dword Id, byte   * * parms, byte Info_Sent_Flag)
{
  word i;
  byte   * ie;
  word Info_Number;
  byte   * Info_Element;
  word Info_Mask = 0;

  dbug(1,dprintf("SetupInfo"));

  for(i=0; i<MAXPARMSIDS; i++) {
    ie = parms[i];
    Info_Number = 0;
    Info_Element = ie;
    if(ie[0]) {
      switch(i) {
      case 0:
        dbug(1,dprintf("CPN "));
        Info_Number = 0x0070;
        Info_Mask   = 0x80;
        Info_Sent_Flag = true;
        break;
      case 8:  /* display      */
        dbug(1,dprintf("display(%d)",i));
        Info_Number = 0x0028;
        Info_Mask = 0x04;
        Info_Sent_Flag = true;
        break;
      case 16: /* Channel Id */
        dbug(1,dprintf("CHI"));
        Info_Number = 0x0018;
        Info_Mask = 0x100;
        Info_Sent_Flag = true;
        mixer_set_bchannel_id (plci, Info_Element);
        break;
      case 19: /* Redirected Number */
        dbug(1,dprintf("RDN"));
        Info_Number = 0x0074;
        Info_Mask = 0x400;
        Info_Sent_Flag = true;
        break;
      case 20: /* Redirected Number extended */
        dbug(1,dprintf("RDX"));
        Info_Number = 0x0073;
        Info_Mask = 0x400;
        Info_Sent_Flag = true;
        break;
      case 22: /* Redirecing Number  */
        dbug(1,dprintf("RIN"));
        Info_Number = 0x0076;
        Info_Mask = 0x400;
        Info_Sent_Flag = true;
        break;
      default:
        Info_Number = 0;
        break;
      }
    }

    if(i==MAXPARMSIDS-2){ /* to indicate the message type "Setup" */
      Info_Number = 0x8000 |5;
      Info_Mask = 0x10;
      Info_Element = "";
    }

    if(Info_Sent_Flag && Info_Number){
      if(plci->adapter->Info_Mask[appl->Id-1] & Info_Mask) {
        sendf(appl,_INFO_I,Id,0,"wS",Info_Number,Info_Element);
      }
    }
  }
}