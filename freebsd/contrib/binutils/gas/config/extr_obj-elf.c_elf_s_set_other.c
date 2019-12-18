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
typedef  int /*<<< orphan*/  symbolS ;

/* Variables and functions */
 int /*<<< orphan*/  S_SET_OTHER (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
elf_s_set_other (symbolS *sym, int other)
{
  S_SET_OTHER (sym, other);
}