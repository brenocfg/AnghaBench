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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  _BitScanReverse64 (unsigned long*,int /*<<< orphan*/ ) ; 

int32_t BUILDIN_CLZL(uint64_t val) {
  unsigned long r = 0;
  _BitScanReverse64(&r, val);
  return (int)(r >> 3);
}