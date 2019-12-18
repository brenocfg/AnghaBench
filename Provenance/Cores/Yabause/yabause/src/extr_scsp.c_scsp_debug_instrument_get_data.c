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
struct TYPE_2__ {int is_muted; int /*<<< orphan*/  sa; } ;

/* Variables and functions */
 int NUM_DEBUG_INSTRUMENTS ; 
 TYPE_1__* debug_instruments ; 

void scsp_debug_instrument_get_data(int i, u32 * sa, int * is_muted)
{
   if(i >= NUM_DEBUG_INSTRUMENTS)
      return;

   *sa = debug_instruments[i].sa;
   *is_muted = debug_instruments[i].is_muted;
}