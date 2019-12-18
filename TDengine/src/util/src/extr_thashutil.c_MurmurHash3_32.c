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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MurmurHash3_32_s (void const*,int,int const,int /*<<< orphan*/ *) ; 

uint32_t MurmurHash3_32(const void *key, int len) {
  const int32_t hashSeed = 0x12345678;

  uint32_t val = 0;
  MurmurHash3_32_s(key, len, hashSeed, &val);

  return val;
}