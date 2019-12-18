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
struct TYPE_2__ {scalar_t__ in_lboards; scalar_t__ in_cheevos; } ;
typedef  TYPE_1__ rcheevos_readud_t ;

/* Variables and functions */

__attribute__((used)) static int rcheevos_read_end_array(void* userdata)
{
   rcheevos_readud_t* ud = (rcheevos_readud_t*)userdata;

   ud->in_cheevos       = 0;
   ud->in_lboards       = 0;
   return 0;
}