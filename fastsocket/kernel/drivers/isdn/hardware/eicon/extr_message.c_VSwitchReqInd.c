#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t word ;
typedef  int /*<<< orphan*/  dword ;
typedef  int byte ;
struct TYPE_9__ {int vswitchstate; int /*<<< orphan*/  internal_command; int /*<<< orphan*/  command; int /*<<< orphan*/  ptyState; } ;
struct TYPE_7__ {scalar_t__ Ind; } ;
struct TYPE_8__ {int vswitchstate; int vsprot; int vsprotdialect; TYPE_3__* relatedPTYPLCI; int /*<<< orphan*/  ptyState; TYPE_1__ Sig; int /*<<< orphan*/  State; int /*<<< orphan*/  appl; } ;
typedef  TYPE_2__ PLCI ;

/* Variables and functions */
 int /*<<< orphan*/  ESC ; 
 size_t MAX_MULTI_IE ; 
 scalar_t__ NCR_FACILITY ; 
 int /*<<< orphan*/  S_ECT ; 
#define  VSJOIN 129 
#define  VSTRANSPORT 128 
 int VSWITCHIE ; 
 int VSWITCH_IND ; 
 int VSWITCH_REQ ; 
 int /*<<< orphan*/  VSWITCH_REQ_PEND ; 
 int /*<<< orphan*/  add_p (TYPE_3__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int) ; 
 int /*<<< orphan*/  send_req (TYPE_3__*) ; 
 int /*<<< orphan*/  sig_req (TYPE_3__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void VSwitchReqInd(PLCI   *plci, dword Id, byte   **parms)
{
 word i;
 /* Format of vswitch_t:
 0 byte length
 1 byte VSWITCHIE
 2 byte VSWITCH_REQ/VSWITCH_IND
 3 byte reserved
 4 word VSwitchcommand
 6 word returnerror
 8... Params
 */
 if(!plci ||
  !plci->appl ||
  !plci->State ||
  plci->Sig.Ind==NCR_FACILITY
  )
  return;
 
 for(i=0;i<MAX_MULTI_IE;i++)
 {
        if(!parms[i][0]) continue;
  if(parms[i][0]<7)
  {
   parms[i][0]=0; /* kill it */
   continue;
  }
  dbug(1,dprintf("VSwitchReqInd(%d)",parms[i][4]));
  switch(parms[i][4])
  {
  case VSJOIN:
   if(!plci->relatedPTYPLCI ||
    (plci->ptyState!=S_ECT && plci->relatedPTYPLCI->ptyState!=S_ECT))
   { /* Error */
    break;
   }
   /* remember all necessary informations */
   if(parms[i][0]!=11 || parms[i][8]!=3) /* Length Test */
   {
    break;
   }
   if(parms[i][2]==VSWITCH_IND && parms[i][9]==1)
   {   /* first indication after ECT-Request on Consultation Call */
    plci->vswitchstate=parms[i][9];
    parms[i][9]=2; /* State */
    /* now ask first Call to join */
   }
   else if(parms[i][2]==VSWITCH_REQ && parms[i][9]==3)
   { /* Answer of VSWITCH_REQ from first Call */
    plci->vswitchstate=parms[i][9];
    /* tell consultation call to join
    and the protocol capabilities of the first call */
   }
   else
   { /* Error */
    break;
   }    
   plci->vsprot=parms[i][10]; /* protocol */
   plci->vsprotdialect=parms[i][11]; /* protocoldialect */
   /* send join request to related PLCI */
   parms[i][1]=VSWITCHIE;
   parms[i][2]=VSWITCH_REQ;
   
   plci->relatedPTYPLCI->command = 0;
   plci->relatedPTYPLCI->internal_command = VSWITCH_REQ_PEND;
   add_p(plci->relatedPTYPLCI,ESC,&parms[i][0]);
   sig_req(plci->relatedPTYPLCI,VSWITCH_REQ,0);
   send_req(plci->relatedPTYPLCI);
   break;
  case VSTRANSPORT:
  default:
   if(plci->relatedPTYPLCI &&
    plci->vswitchstate==3 &&
    plci->relatedPTYPLCI->vswitchstate==3)
   {
    add_p(plci->relatedPTYPLCI,ESC,&parms[i][0]);
    sig_req(plci->relatedPTYPLCI,VSWITCH_REQ,0);
    send_req(plci->relatedPTYPLCI);
   }
   break;
  }  
  parms[i][0]=0; /* kill it */
 }
}