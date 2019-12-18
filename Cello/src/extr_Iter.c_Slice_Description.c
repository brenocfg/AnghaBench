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

/* Variables and functions */

__attribute__((used)) static const char* Slice_Description(void) {
  return
    "The `Slice` type is an iterable that allows one to only iterate over "
    "part of another iterable. Given some start, stop and step, only "
    "those entries described by the `Slice` are returned in the iteration."
    "\n\n"
    "Under the hood the `Slice` object still iterates over the whole iterable "
    "but it only returns those values in the range given.";
}