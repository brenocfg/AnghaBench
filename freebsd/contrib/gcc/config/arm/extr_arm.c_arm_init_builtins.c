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
 scalar_t__ TARGET_REALLY_IWMMXT ; 
 int /*<<< orphan*/  arm_init_iwmmxt_builtins () ; 
 int /*<<< orphan*/  arm_init_tls_builtins () ; 

__attribute__((used)) static void
arm_init_builtins (void)
{
  arm_init_tls_builtins ();

  if (TARGET_REALLY_IWMMXT)
    arm_init_iwmmxt_builtins ();
}