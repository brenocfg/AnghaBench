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
typedef  int word ;
typedef  size_t byte ;
struct TYPE_5__ {size_t* ch_ncci; size_t* ncci_ch; size_t* ncci_next; int /*<<< orphan*/ * ncci_state; int /*<<< orphan*/ * ncci_plci; } ;
struct TYPE_4__ {int ncci_ring_list; int /*<<< orphan*/  Id; TYPE_2__* adapter; } ;
typedef  TYPE_1__ PLCI ;
typedef  TYPE_2__ DIVA_CAPI_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  IDLE ; 
 int MAX_NCCI ; 
 int MAX_NL_CHANNEL ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,size_t,int,...) ; 
 int /*<<< orphan*/  ncci_mapping_bug ; 

__attribute__((used)) static word get_ncci (PLCI   *plci, byte ch, word force_ncci)
{
  DIVA_CAPI_ADAPTER   *a;
  word ncci, i, j, k;

  a = plci->adapter;
  if (!ch || a->ch_ncci[ch])
  {
    ncci_mapping_bug++;
    dbug(1,dprintf("NCCI mapping exists %ld %02x %02x %02x-%02x",
      ncci_mapping_bug, ch, force_ncci, a->ncci_ch[a->ch_ncci[ch]], a->ch_ncci[ch]));
    ncci = ch;
  }
  else
  {
    if (force_ncci)
      ncci = force_ncci;
    else
    {
      if ((ch < MAX_NCCI+1) && !a->ncci_ch[ch])
        ncci = ch;
      else
      {
        ncci = 1;
        while ((ncci < MAX_NCCI+1) && a->ncci_ch[ncci])
          ncci++;
        if (ncci == MAX_NCCI+1)
        {
          ncci_mapping_bug++;
          i = 1;
          do
          {
            j = 1;
            while ((j < MAX_NCCI+1) && (a->ncci_ch[j] != i))
              j++;
            k = j;
            if (j < MAX_NCCI+1)
            {
              do
              {
                j++;
              } while ((j < MAX_NCCI+1) && (a->ncci_ch[j] != i));
            }
          } while ((i < MAX_NL_CHANNEL+1) && (j < MAX_NCCI+1));
          if (i < MAX_NL_CHANNEL+1)
          {
            dbug(1,dprintf("NCCI mapping overflow %ld %02x %02x %02x-%02x-%02x",
              ncci_mapping_bug, ch, force_ncci, i, k, j));
          }
          else
          {
            dbug(1,dprintf("NCCI mapping overflow %ld %02x %02x",
              ncci_mapping_bug, ch, force_ncci));
          }
          ncci = ch;
        }
      }
      a->ncci_plci[ncci] = plci->Id;
      a->ncci_state[ncci] = IDLE;
      if (!plci->ncci_ring_list)
        plci->ncci_ring_list = ncci;
      else
        a->ncci_next[ncci] = a->ncci_next[plci->ncci_ring_list];
      a->ncci_next[plci->ncci_ring_list] = (byte) ncci;
    }
    a->ncci_ch[ncci] = ch;
    a->ch_ncci[ch] = (byte) ncci;
    dbug(1,dprintf("NCCI mapping established %ld %02x %02x %02x-%02x",
      ncci_mapping_bug, ch, force_ncci, ch, ncci));
  }
  return (ncci);
}