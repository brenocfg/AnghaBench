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

__attribute__((used)) static int
is_quarter_float (unsigned imm)
{
  int bs = (imm & 0x20000000) ? 0x3e000000 : 0x40000000;
  return (imm & 0x7ffff) == 0 && ((imm & 0x7e000000) ^ bs) == 0;
}