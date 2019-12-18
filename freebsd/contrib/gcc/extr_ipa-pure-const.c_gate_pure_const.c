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
 scalar_t__ errorcount ; 
 scalar_t__ flag_ipa_pure_const ; 
 scalar_t__ flag_unit_at_a_time ; 
 scalar_t__ sorrycount ; 

__attribute__((used)) static bool
gate_pure_const (void)
{
  return (flag_unit_at_a_time != 0 && flag_ipa_pure_const 
	  /* Don't bother doing anything if the program has errors.  */
	  && !(errorcount || sorrycount));
}