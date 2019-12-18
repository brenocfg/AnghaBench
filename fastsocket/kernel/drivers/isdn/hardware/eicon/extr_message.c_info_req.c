#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
typedef  int /*<<< orphan*/  dword ;
typedef  int byte ;
struct TYPE_22__ {scalar_t__ length; int /*<<< orphan*/ * info; } ;
struct TYPE_21__ {int NullCREnable; } ;
struct TYPE_20__ {TYPE_1__* plci; } ;
struct TYPE_19__ {TYPE_3__* appl; int /*<<< orphan*/  internal_command; scalar_t__ State; } ;
typedef  TYPE_1__ PLCI ;
typedef  TYPE_2__ DIVA_CAPI_ADAPTER ;
typedef  TYPE_3__ APPL ;
typedef  TYPE_4__ API_PARSE ;

/* Variables and functions */
 int /*<<< orphan*/  ASSIGN ; 
 int /*<<< orphan*/  CAI ; 
 int CONFIRM ; 
 int /*<<< orphan*/  CPN ; 
 int /*<<< orphan*/  C_NCR_FAC_REQ ; 
 int /*<<< orphan*/  DSIG_ID ; 
 int /*<<< orphan*/  FACILITY_REQ ; 
 int /*<<< orphan*/  INFO_REQ ; 
 int /*<<< orphan*/  KEY ; 
 int /*<<< orphan*/  NCR_FACILITY ; 
 int /*<<< orphan*/  UID ; 
 int /*<<< orphan*/  USER_DATA ; 
 int /*<<< orphan*/  UUI ; 
 int _INFO_R ; 
 int _OUT_OF_PLCI ; 
 int _WRONG_MESSAGE_FORMAT ; 
 int _WRONG_STATE ; 
 int /*<<< orphan*/  add_ai (TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  add_p (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_s (TYPE_1__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ api_parse (int /*<<< orphan*/ *,int,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int get_plci (TYPE_2__*) ; 
 int /*<<< orphan*/  send_req (TYPE_1__*) ; 
 int /*<<< orphan*/  sendf (TYPE_3__*,int,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  sig_req (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static byte info_req(dword Id, word Number, DIVA_CAPI_ADAPTER *a,
		     PLCI *plci, APPL *appl, API_PARSE *msg)
{
  word i;
  API_PARSE * ai;
  PLCI   * rc_plci = NULL;
    API_PARSE ai_parms[5];
  word Info = 0;

  dbug(1,dprintf("info_req"));
  for(i=0;i<5;i++) ai_parms[i].length = 0;

  ai = &msg[1];

  if(ai->length)
  {
    if(api_parse(&ai->info[1],(word)ai->length,"ssss",ai_parms))
    {
      dbug(1,dprintf("AddInfo wrong"));
      Info = _WRONG_MESSAGE_FORMAT;
    }
  }
  if(!a) Info = _WRONG_STATE;

  if(!Info && plci)
  {                /* no fac, with CPN, or KEY */
    rc_plci = plci;
    if(!ai_parms[3].length && plci->State && (msg[0].length || ai_parms[1].length) )
    {
      /* overlap sending option */
      dbug(1,dprintf("OvlSnd"));
      add_s(plci,CPN,&msg[0]);
      add_s(plci,KEY,&ai_parms[1]);
      sig_req(plci,INFO_REQ,0);
      send_req(plci);
      return false;
    }

    if(plci->State && ai_parms[2].length)
    {
      /* User_Info option */
      dbug(1,dprintf("UUI"));
      add_s(plci,UUI,&ai_parms[2]);
      sig_req(plci,USER_DATA,0);
    }
    else if(plci->State && ai_parms[3].length)
    {
      /* Facility option */
      dbug(1,dprintf("FAC"));
      add_s(plci,CPN,&msg[0]);
      add_ai(plci, &msg[1]);
      sig_req(plci,FACILITY_REQ,0);
    }
    else
    {
      Info = _WRONG_STATE;
    }
  }
  else if((ai_parms[1].length || ai_parms[2].length || ai_parms[3].length) && !Info)
  {
    /* NCR_Facility option -> send UUI and Keypad too */
    dbug(1,dprintf("NCR_FAC"));
    if((i=get_plci(a)))
    {
      rc_plci = &a->plci[i-1];
      appl->NullCREnable  = true;
      rc_plci->internal_command = C_NCR_FAC_REQ;
      rc_plci->appl = appl;
      add_p(rc_plci,CAI,"\x01\x80");
      add_p(rc_plci,UID,"\x06\x43\x61\x70\x69\x32\x30");
      sig_req(rc_plci,ASSIGN,DSIG_ID);
      send_req(rc_plci);
    }
    else
    {
      Info = _OUT_OF_PLCI;
    }

    if(!Info)
    {
      add_s(rc_plci,CPN,&msg[0]);
      add_ai(rc_plci, &msg[1]);
      sig_req(rc_plci,NCR_FACILITY,0);
      send_req(rc_plci);
      return false;
     /* for application controlled supplementary services    */
    }
  }

  if (!rc_plci)
  {
    Info = _WRONG_MESSAGE_FORMAT;
  }

  if(!Info)
  {
    send_req(rc_plci);
  }
  else
  {  /* appl is not assigned to a PLCI or error condition */
    dbug(1,dprintf("localInfoCon"));
    sendf(appl,
          _INFO_R|CONFIRM,
          Id,
          Number,
          "w",Info);
  }
  return false;
}