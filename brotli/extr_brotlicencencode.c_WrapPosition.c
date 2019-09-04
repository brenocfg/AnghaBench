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
typedef  unsigned int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t WrapPosition(uint64_t position) {
  uint32_t result = (uint32_t)position;
  uint64_t gb = position >> 30;
  if (gb > 2) {
    /* Wrap every 2GiB; The first 3GB are continuous. */
    result = (result & ((1u << 30) - 1)) | ((uint32_t)((gb - 1) & 1) + 1) << 30;
  }
  return result;
}