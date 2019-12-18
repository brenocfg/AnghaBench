#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t word ;
typedef  int dword ;
typedef  int byte ;
struct TYPE_9__ {int /*<<< orphan*/ * ncci_state; } ;
struct TYPE_8__ {int B3_prot; } ;
typedef  TYPE_1__ PLCI ;
typedef  TYPE_2__ DIVA_CAPI_ADAPTER ;
typedef  int /*<<< orphan*/  APPL ;
typedef  int /*<<< orphan*/  API_PARSE ;

/* Variables and functions */
#define  B3_ISO8208 130 
#define  B3_TRANSPARENT 129 
#define  B3_X25_DCE 128 
 int CONFIRM ; 
 int /*<<< orphan*/  CONNECTED ; 
 size_t GOOD ; 
 int /*<<< orphan*/  N_RESET ; 
 int _RESET_B3_R ; 
 size_t _WRONG_IDENTIFIER ; 
 size_t _WRONG_STATE ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  nl_req_ncci (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_b3_command ; 
 int /*<<< orphan*/  send_req (TYPE_1__*) ; 
 int /*<<< orphan*/  sendf (int /*<<< orphan*/ *,int,int,size_t,char*,size_t) ; 
 int /*<<< orphan*/  start_internal_command (int,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static byte reset_b3_req(dword Id, word Number, DIVA_CAPI_ADAPTER *a,
			 PLCI *plci, APPL *appl, API_PARSE *parms)
{
  word Info;
  word ncci;

  dbug(1,dprintf("reset_b3_req"));

  Info = _WRONG_IDENTIFIER;
  ncci = (word)(Id>>16);
  if(plci && ncci)
  {
    Info = _WRONG_STATE;
    switch (plci->B3_prot)
    {
    case B3_ISO8208:
    case B3_X25_DCE:
      if(a->ncci_state[ncci]==CONNECTED)
      {
        nl_req_ncci(plci,N_RESET,(byte)ncci);
        send_req(plci);
        Info = GOOD;
      }
      break;
    case B3_TRANSPARENT:
      if(a->ncci_state[ncci]==CONNECTED)
      {
        start_internal_command (Id, plci, reset_b3_command);
        Info = GOOD;
      }
      break;
    }
  }
  /* reset_b3 must result in a reset_b3_con & reset_b3_Ind */
  sendf(appl,
        _RESET_B3_R|CONFIRM,
        Id,
        Number,
        "w",Info);
  return false;
}