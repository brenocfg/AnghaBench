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

__attribute__((used)) static unsigned
neon_squash_bits (unsigned imm)
{
  return (imm & 0x01) | ((imm & 0x0100) >> 7) | ((imm & 0x010000) >> 14)
         | ((imm & 0x01000000) >> 21);
}