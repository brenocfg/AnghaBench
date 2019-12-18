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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  write_32bit_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_64bit_value(uint64_t i) {
  // GCOV uses a lo-/hi-word format even on big-endian systems.
  // See also GCOVBuffer::readInt64 in LLVM.
  uint32_t lo = (uint32_t) i;
  uint32_t hi = (uint32_t) (i >> 32);
  write_32bit_value(lo);
  write_32bit_value(hi);
}