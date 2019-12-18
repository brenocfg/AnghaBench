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
typedef  int bfd_boolean ;

/* Variables and functions */

__attribute__((used)) static bfd_boolean
is_branch (const unsigned char *insn)
{
  return (insn[0] & 0xec) == 0x20 && (insn[1] & 0x80) == 0;
}