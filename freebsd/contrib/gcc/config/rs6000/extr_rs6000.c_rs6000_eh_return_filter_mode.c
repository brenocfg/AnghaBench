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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int SImode ; 
 scalar_t__ TARGET_32BIT ; 
 int word_mode ; 

__attribute__((used)) static enum machine_mode
rs6000_eh_return_filter_mode (void)
{
  return TARGET_32BIT ? SImode : word_mode;
}