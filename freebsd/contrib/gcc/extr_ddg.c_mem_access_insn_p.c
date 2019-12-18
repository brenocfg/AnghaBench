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
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 int rtx_mem_access_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
mem_access_insn_p (rtx insn)
{
  return rtx_mem_access_p (PATTERN (insn));
}