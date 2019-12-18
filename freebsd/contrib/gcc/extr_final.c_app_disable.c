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
 int /*<<< orphan*/  ASM_APP_OFF ; 
 scalar_t__ app_on ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
app_disable (void)
{
  if (app_on)
    {
      fputs (ASM_APP_OFF, asm_out_file);
      app_on = 0;
    }
}