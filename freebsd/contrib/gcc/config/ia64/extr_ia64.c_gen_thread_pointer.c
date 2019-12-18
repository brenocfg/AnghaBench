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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 scalar_t__ thread_pointer_rtx ; 

__attribute__((used)) static rtx
gen_thread_pointer (void)
{
  if (!thread_pointer_rtx)
    thread_pointer_rtx = gen_rtx_REG (Pmode, 13);
  return thread_pointer_rtx;
}