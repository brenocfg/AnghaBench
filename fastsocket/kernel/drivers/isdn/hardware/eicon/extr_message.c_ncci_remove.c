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
typedef  int word ;
typedef  int dword ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_7__ {int Id; scalar_t__* ncci_plci; size_t* ncci_ch; int* ncci_next; void** ncci_state; scalar_t__* ch_ncci; } ;
struct TYPE_6__ {scalar_t__ Id; int ncci_ring_list; TYPE_2__* adapter; } ;
typedef  TYPE_1__ PLCI ;
typedef  TYPE_2__ DIVA_CAPI_ADAPTER ;

/* Variables and functions */
 void* IDLE ; 
 int MAX_NCCI ; 
 int /*<<< orphan*/  cleanup_ncci_data (TYPE_1__*,int) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ncci_free_receive_buffers (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ncci_mapping_bug ; 

__attribute__((used)) static void ncci_remove (PLCI   *plci, word ncci, byte preserve_ncci)
{
  DIVA_CAPI_ADAPTER   *a;
  dword Id;
  word i;

  a = plci->adapter;
  Id = (((dword) ncci) << 16) | (((word)(plci->Id)) << 8) | a->Id;
  if (!preserve_ncci)
    ncci_free_receive_buffers (plci, ncci);
  if (ncci)
  {
    if (a->ncci_plci[ncci] != plci->Id)
    {
      ncci_mapping_bug++;
      dbug(1,dprintf("NCCI mapping doesn't exist %ld %08lx %02x",
        ncci_mapping_bug, Id, preserve_ncci));
    }
    else
    {
      cleanup_ncci_data (plci, ncci);
      dbug(1,dprintf("NCCI mapping released %ld %08lx %02x %02x-%02x",
        ncci_mapping_bug, Id, preserve_ncci, a->ncci_ch[ncci], ncci));
      a->ch_ncci[a->ncci_ch[ncci]] = 0;
      if (!preserve_ncci)
      {
        a->ncci_ch[ncci] = 0;
        a->ncci_plci[ncci] = 0;
        a->ncci_state[ncci] = IDLE;
        i = plci->ncci_ring_list;
        while ((i != 0) && (a->ncci_next[i] != plci->ncci_ring_list) && (a->ncci_next[i] != ncci))
          i = a->ncci_next[i];
        if ((i != 0) && (a->ncci_next[i] == ncci))
        {
          if (i == ncci)
            plci->ncci_ring_list = 0;
          else if (plci->ncci_ring_list == ncci)
            plci->ncci_ring_list = i;
          a->ncci_next[i] = a->ncci_next[ncci];
        }
        a->ncci_next[ncci] = 0;
      }
    }
  }
  else
  {
    for (ncci = 1; ncci < MAX_NCCI+1; ncci++)
    {
      if (a->ncci_plci[ncci] == plci->Id)
      {
        cleanup_ncci_data (plci, ncci);
        dbug(1,dprintf("NCCI mapping released %ld %08lx %02x %02x-%02x",
          ncci_mapping_bug, Id, preserve_ncci, a->ncci_ch[ncci], ncci));
        a->ch_ncci[a->ncci_ch[ncci]] = 0;
        if (!preserve_ncci)
        {
          a->ncci_ch[ncci] = 0;
          a->ncci_plci[ncci] = 0;
          a->ncci_state[ncci] = IDLE;
          a->ncci_next[ncci] = 0;
        }
      }
    }
    if (!preserve_ncci)
      plci->ncci_ring_list = 0;
  }
}