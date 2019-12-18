#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int isaudio; } ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 TYPE_2__* Cs2Area ; 
 int /*<<< orphan*/  Cs2SetTiming (int) ; 
 int /*<<< orphan*/  SCSPLOG (char*) ; 
 int cdda_next_in ; 
 int cdda_out_left ; 
 TYPE_1__ cddabuf ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,int) ; 

void
ScspReceiveCDDA (const u8 *sector)
{
   // If buffer is half empty or less, boost timing for a bit until we've buffered a few sectors
   if (cdda_out_left < (sizeof(cddabuf.data) / 2))
   {
      Cs2Area->isaudio = 0;
      Cs2SetTiming(1);
		Cs2Area->isaudio = 1;
   }
	else if (cdda_out_left > (sizeof(cddabuf.data) * 3 / 4 ))
		Cs2SetTiming(0);
   else
   {
      Cs2Area->isaudio = 1;
      Cs2SetTiming(1);
   }

  memcpy(cddabuf.data+cdda_next_in, sector, 2352);
  if (sizeof(cddabuf.data)-cdda_next_in <= 2352)
     cdda_next_in = 0;
  else
     cdda_next_in += 2352;

  cdda_out_left += 2352;

  if (cdda_out_left > sizeof(cddabuf.data))
    {
      SCSPLOG ("WARNING: CDDA buffer overrun\n");
      cdda_out_left = sizeof(cddabuf.data);
    }
}