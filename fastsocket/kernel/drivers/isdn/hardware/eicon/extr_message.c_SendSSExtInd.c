#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t word ;
typedef  int /*<<< orphan*/  dword ;
typedef  int byte ;
struct TYPE_4__ {scalar_t__ Ind; } ;
struct TYPE_5__ {int /*<<< orphan*/ * appl; TYPE_1__ Sig; scalar_t__ State; } ;
typedef  TYPE_2__ PLCI ;
typedef  int /*<<< orphan*/  APPL ;

/* Variables and functions */
 size_t MAX_MULTI_IE ; 
 scalar_t__ NCR_FACILITY ; 
 int SSEXT_REQ ; 
 int /*<<< orphan*/  _DI_MANU_ID ; 
 int /*<<< orphan*/  _DI_SSEXT_CTRL ; 
 int /*<<< orphan*/  _MANUFACTURER_I ; 
 int /*<<< orphan*/  sendf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void SendSSExtInd(APPL   * appl, PLCI   * plci, dword Id, byte   * * parms)
{
  word i;
   /* Format of multi_ssext_parms[i][]:
   0 byte length
   1 byte SSEXTIE
   2 byte SSEXT_REQ/SSEXT_IND
   3 byte length
   4 word SSExtCommand
   6... Params
   */
  if(
   plci
   && plci->State
   && plci->Sig.Ind!=NCR_FACILITY
    )
 for(i=0;i<MAX_MULTI_IE;i++)
    {
      if(parms[i][0]<6) continue;
   if(parms[i][2]==SSEXT_REQ) continue;

   if(appl)
   {
    parms[i][0]=0; /* kill it */
    sendf(appl,_MANUFACTURER_I,
    Id,
    0,
    "dwS",
    _DI_MANU_ID,
    _DI_SSEXT_CTRL,
    &parms[i][3]);
   }
   else if(plci->appl)
   {
    parms[i][0]=0; /* kill it */
    sendf(plci->appl,_MANUFACTURER_I,
    Id,
    0,
    "dwS",
    _DI_MANU_ID,
    _DI_SSEXT_CTRL,
    &parms[i][3]);
   }
    }
}