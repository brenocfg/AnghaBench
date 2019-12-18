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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  sa; } ;

/* Variables and functions */
 scalar_t__ NUM_DEBUG_INSTRUMENTS ; 
 scalar_t__ debug_instrument_pos ; 
 TYPE_1__* debug_instruments ; 
 int /*<<< orphan*/  scsp_debug_search_instruments (int /*<<< orphan*/ ,int*,int*) ; 

void scsp_debug_add_instrument(u32 sa)
{
   int i = 0, found = 0, offset = 0;

   if (debug_instrument_pos >= NUM_DEBUG_INSTRUMENTS)
      return;

   scsp_debug_search_instruments(sa, &found, &offset);

   //new instrument discovered
   if (!found)
      debug_instruments[debug_instrument_pos++].sa = sa;
}