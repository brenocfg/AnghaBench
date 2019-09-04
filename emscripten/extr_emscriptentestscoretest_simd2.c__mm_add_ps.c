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
typedef  scalar_t__ __m128 ;

/* Variables and functions */

__attribute__((used)) static inline __m128 __attribute__((always_inline))
    _mm_add_ps(__m128 __A, __m128 __B) {
  return __A + __B;
}