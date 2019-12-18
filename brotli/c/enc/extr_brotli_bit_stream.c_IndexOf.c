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
typedef  scalar_t__ const uint8_t ;

/* Variables and functions */

__attribute__((used)) static size_t IndexOf(const uint8_t* v, size_t v_size, uint8_t value) {
  size_t i = 0;
  for (; i < v_size; ++i) {
    if (v[i] == value) return i;
  }
  return i;
}