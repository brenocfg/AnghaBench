#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int status; int _periodictiming; int _periodiccycles; } ;

/* Variables and functions */
 int CDB_STAT_PLAY ; 
 TYPE_1__* Cs2Area ; 

int Cs2GetTimeToNextSector(void) {
   if ((Cs2Area->status & 0xF) != CDB_STAT_PLAY) {
      return 0;
   } else {
      // Round up, since the caller wants to know when it'll be safe to check
      int time = (Cs2Area->_periodictiming - Cs2Area->_periodiccycles + 2) / 3;
      return time<0 ? 0 : time;
   }
}