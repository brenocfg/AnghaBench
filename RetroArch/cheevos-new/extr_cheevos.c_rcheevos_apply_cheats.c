#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int rcheevos_cheats_are_enabled ; 
 int rcheevos_cheats_were_enabled ; 

bool rcheevos_apply_cheats(bool* data_bool)
{
   rcheevos_cheats_are_enabled   = *data_bool;
   rcheevos_cheats_were_enabled |= rcheevos_cheats_are_enabled;

   return true;
}