#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
typedef  int dword ;
typedef  scalar_t__ byte ;
struct TYPE_7__ {int MaxBuffer; int* DataNCCI; int* DataFlags; } ;
struct TYPE_6__ {int Id; scalar_t__* ncci_plci; } ;
struct TYPE_5__ {scalar_t__ Id; TYPE_3__* appl; TYPE_2__* adapter; } ;
typedef  TYPE_1__ PLCI ;
typedef  TYPE_2__ DIVA_CAPI_ADAPTER ;
typedef  TYPE_3__ APPL ;

/* Variables and functions */
 int MAX_NCCI ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ncci_mapping_bug ; 

__attribute__((used)) static void ncci_free_receive_buffers (PLCI   *plci, word ncci)
{
  DIVA_CAPI_ADAPTER   *a;
  APPL   *appl;
  word i, ncci_code;
  dword Id;

  a = plci->adapter;
  Id = (((dword) ncci) << 16) | (((word)(plci->Id)) << 8) | a->Id;
  if (ncci)
  {
    if (a->ncci_plci[ncci] == plci->Id)
    {
      if (!plci->appl)
      {
        ncci_mapping_bug++;
        dbug(1,dprintf("NCCI mapping appl expected %ld %08lx",
          ncci_mapping_bug, Id));
      }
      else
      {
        appl = plci->appl;
        ncci_code = ncci | (((word) a->Id) << 8);
        for (i = 0; i < appl->MaxBuffer; i++)
        {
          if ((appl->DataNCCI[i] == ncci_code)
           && (((byte)(appl->DataFlags[i] >> 8)) == plci->Id))
          {
            appl->DataNCCI[i] = 0;
          }
        }
      }
    }
  }
  else
  {
    for (ncci = 1; ncci < MAX_NCCI+1; ncci++)
    {
      if (a->ncci_plci[ncci] == plci->Id)
      {
        if (!plci->appl)
        {
          ncci_mapping_bug++;
          dbug(1,dprintf("NCCI mapping no appl %ld %08lx",
            ncci_mapping_bug, Id));
        }
        else
        {
          appl = plci->appl;
          ncci_code = ncci | (((word) a->Id) << 8);
          for (i = 0; i < appl->MaxBuffer; i++)
          {
            if ((appl->DataNCCI[i] == ncci_code)
             && (((byte)(appl->DataFlags[i] >> 8)) == plci->Id))
            {
              appl->DataNCCI[i] = 0;
            }
          }
        }
      }
    }
  }
}