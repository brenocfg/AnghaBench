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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */

__attribute__((used)) static void MoveToFront(uint8_t* v, size_t index) {
  uint8_t value = v[index];
  size_t i;
  for (i = index; i != 0; --i) {
    v[i] = v[i - 1];
  }
  v[0] = value;
}