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
struct timer {int /*<<< orphan*/  all_bits; } ;

/* Variables and functions */

__attribute__((used)) static uint64_t safe_grab_timer_value(struct timer *t)
{
#if   defined(__LP64__)
  return t->all_bits;
#else
  uint64_t time = t->high_bits;    /* endian independent grab */
  time = (time << 32) | t->low_bits;
  return time;
#endif
}