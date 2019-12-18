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
 scalar_t__ inf_mode_valid ; 
 int terminal_is_ours ; 

__attribute__((used)) static void
go32_terminal_init (void)
{
  inf_mode_valid = 0;	/* reinitialize, in case they are restarting child */
  terminal_is_ours = 1;
}