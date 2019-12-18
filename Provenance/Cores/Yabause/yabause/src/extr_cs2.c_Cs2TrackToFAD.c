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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int* TOC; } ;

/* Variables and functions */
 TYPE_1__* Cs2Area ; 

u32 Cs2TrackToFAD(u16 trackandindex) {
  if (trackandindex == 0xFFFF)
     // leadout position
     return (Cs2Area->TOC[101] & 0x00FFFFFF);
  if (trackandindex != 0x0000)
  {
     // regular track
     // (really, we should be fetching subcode q's here)
     if ((trackandindex & 0xFF) == 0x01)
        // Return Start of Track
        return (Cs2Area->TOC[(trackandindex >> 8) - 1] & 0x00FFFFFF);
     else if ((trackandindex & 0xFF) == 0x63)
        // Return End of Track
        return ((Cs2Area->TOC[(trackandindex >> 8)] & 0x00FFFFFF) - 1);
  }

  // assume it's leadin
  return 0;
}