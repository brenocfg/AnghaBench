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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ TARGET_ARCH64 ; 
 int /*<<< orphan*/  gen_save_register_windowdi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_save_register_windowsi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
gen_save_register_window (rtx increment)
{
  if (TARGET_ARCH64)
    return gen_save_register_windowdi (increment);
  else
    return gen_save_register_windowsi (increment);
}