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
 int /*<<< orphan*/  CTRLC ; 
 int /*<<< orphan*/  putchar_e7000 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
e7000_stop (void)
{
  /* Sending a ^C is supposed to stop the running program.  */
  putchar_e7000 (CTRLC);
}