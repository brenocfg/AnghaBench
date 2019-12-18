#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t word ;
typedef  int dword ;
typedef  int byte ;
struct TYPE_12__ {int Id; } ;
struct TYPE_9__ {scalar_t__ Ind; } ;
struct TYPE_11__ {TYPE_4__* appl; TYPE_2__* adapter; TYPE_1__ Sig; int /*<<< orphan*/  State; } ;
struct TYPE_10__ {size_t* Info_Mask; } ;
typedef  TYPE_3__ PLCI ;
typedef  TYPE_4__ APPL ;

/* Variables and functions */
 size_t MAX_MULTI_IE ; 
 scalar_t__ NCR_FACILITY ; 
 int /*<<< orphan*/  _INFO_I ; 
 TYPE_4__* application ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 
 size_t max_appl ; 
 int /*<<< orphan*/  sendf (TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,size_t,int*) ; 
 scalar_t__ test_c_ind_mask_bit (TYPE_3__*,size_t) ; 

__attribute__((used)) static byte SendMultiIE(PLCI *plci, dword Id, byte **parms, byte ie_type,
			dword info_mask, byte setupParse)
{
  word i;
  word j;
  byte   * ie;
  word Info_Number;
  byte   * Info_Element;
  APPL   *appl;
  word Info_Mask = 0;
  byte iesent=0;

  if(
      !plci->appl
      && !plci->State
      && plci->Sig.Ind!=NCR_FACILITY
      && !setupParse
      )
  {
    dbug(1,dprintf("NoM-IEParse "));
    return 0;
  }
  dbug(1,dprintf("M-IEParse "));

  for(i=0; i<MAX_MULTI_IE; i++)
  {
    ie = parms[i];
    Info_Number = 0;
    Info_Element = ie;
    if(ie[0])
    {
      dbug(1,dprintf("[Ind0x%x]:IE=0x%x",plci->Sig.Ind,ie_type));
      Info_Number = (word)ie_type;
      Info_Mask = (word)info_mask;
    }

    if(plci->Sig.Ind==NCR_FACILITY)           /* check controller broadcast */
    {
      for(j=0; j<max_appl; j++)
      {
        appl = &application[j];
        if(Info_Number
        && appl->Id
        && plci->adapter->Info_Mask[appl->Id-1] &Info_Mask)
        {
          iesent = true;
          dbug(1,dprintf("Mlt_NCR_Ind"));
          sendf(&application[j],_INFO_I,Id&0x0f,0,"wS",Info_Number,Info_Element);
        }
      }
    }
    else if(!plci->appl && Info_Number)
    {                                        /* overlap receiving broadcast */
      for(j=0; j<max_appl; j++)
      {
        if(test_c_ind_mask_bit (plci, j))
        {
          iesent = true;
          dbug(1,dprintf("Mlt_Ovl_Ind"));
          sendf(&application[j],_INFO_I,Id,0,"wS",Info_Number,Info_Element);
        }
      }
    }                                        /* all other signalling states */
    else if(Info_Number
    && plci->adapter->Info_Mask[plci->appl->Id-1] &Info_Mask)
    {
      iesent = true;
      dbug(1,dprintf("Mlt_Std_Ind"));
      sendf(plci->appl,_INFO_I,Id,0,"wS",Info_Number,Info_Element);
    }
  }
  return iesent;
}