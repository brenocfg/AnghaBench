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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ read_32bit_value () ; 

__attribute__((used)) static uint64_t read_64bit_value() {
  // GCOV uses a lo-/hi-word format even on big-endian systems.
  // See also GCOVBuffer::readInt64 in LLVM.
  uint32_t lo = read_32bit_value();
  uint32_t hi = read_32bit_value();
  return ((uint64_t)hi << 32) | ((uint64_t)lo);
}