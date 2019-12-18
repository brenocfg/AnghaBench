#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char last_seq; unsigned char* sigqual; unsigned char qualptr; int average_fast; int average_slow; int /*<<< orphan*/  last_seen; } ;
typedef  TYPE_1__ wavepoint_history ;

/* Variables and functions */
 int WAVEPOINT_FAST_HISTORY ; 
 unsigned char WAVEPOINT_HISTORY ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static void wl_update_history(wavepoint_history *wavepoint, unsigned char sigqual, unsigned char seq)	
{
  int i=0,num_missed=0,ptr=0;
  int average_fast=0,average_slow=0;
  
  num_missed=(seq-wavepoint->last_seq)%WAVEPOINT_HISTORY;/* Have we missed
							    any beacons? */
  if(num_missed)
    for(i=0;i<num_missed;i++)
      {
	wavepoint->sigqual[wavepoint->qualptr++]=0; /* If so, enter them as 0's */
	wavepoint->qualptr %=WAVEPOINT_HISTORY;    /* in the ringbuffer. */
      }
  wavepoint->last_seen=jiffies;                 /* Add beacon to history */
  wavepoint->last_seq=seq;	
  wavepoint->sigqual[wavepoint->qualptr++]=sigqual;          
  wavepoint->qualptr %=WAVEPOINT_HISTORY;
  ptr=(wavepoint->qualptr-WAVEPOINT_FAST_HISTORY+WAVEPOINT_HISTORY)%WAVEPOINT_HISTORY;
  
  for(i=0;i<WAVEPOINT_FAST_HISTORY;i++)       /* Update running averages */
    {
      average_fast+=wavepoint->sigqual[ptr++];
      ptr %=WAVEPOINT_HISTORY;
    }
  
  average_slow=average_fast;
  for(i=WAVEPOINT_FAST_HISTORY;i<WAVEPOINT_HISTORY;i++)
    {
      average_slow+=wavepoint->sigqual[ptr++];
      ptr %=WAVEPOINT_HISTORY;
    }
  
  wavepoint->average_fast=average_fast/WAVEPOINT_FAST_HISTORY;
  wavepoint->average_slow=average_slow/WAVEPOINT_HISTORY;	
}