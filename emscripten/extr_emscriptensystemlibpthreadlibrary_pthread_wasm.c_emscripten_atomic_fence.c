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
 int /*<<< orphan*/  emscripten_atomic_or_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void emscripten_atomic_fence(void) {
  // Fake a fence with an arbitrary atomic operation
  uint8_t temp = 0;
  emscripten_atomic_or_u8(&temp, 0);
}