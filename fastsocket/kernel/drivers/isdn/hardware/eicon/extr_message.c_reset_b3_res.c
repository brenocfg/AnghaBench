#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t word ;
typedef  int dword ;
typedef  int byte ;
struct TYPE_7__ {int /*<<< orphan*/ * ncci_state; } ;
struct TYPE_6__ {int B3_prot; } ;
typedef  TYPE_1__ PLCI ;
typedef  TYPE_2__ DIVA_CAPI_ADAPTER ;
typedef  int /*<<< orphan*/  APPL ;
typedef  int /*<<< orphan*/  API_PARSE ;

/* Variables and functions */
#define  B3_ISO8208 129 
#define  B3_X25_DCE 128 
 int /*<<< orphan*/  CONNECTED ; 
 int /*<<< orphan*/  INC_RES_PENDING ; 
 int /*<<< orphan*/  N_RESET_ACK ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  nl_req_ncci (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static byte reset_b3_res(dword Id, word Number, DIVA_CAPI_ADAPTER *a,
			 PLCI *plci, APPL *appl, API_PARSE *parms)
{
  word ncci;

  dbug(1,dprintf("reset_b3_res"));

  ncci = (word)(Id>>16);
  if(plci && ncci) {
    switch (plci->B3_prot)
    {
    case B3_ISO8208:
    case B3_X25_DCE:
      if(a->ncci_state[ncci]==INC_RES_PENDING)
      {
        a->ncci_state[ncci] = CONNECTED;
        nl_req_ncci(plci,N_RESET_ACK,(byte)ncci);
        return true;
      }
    break;
    }
  }
  return false;
}