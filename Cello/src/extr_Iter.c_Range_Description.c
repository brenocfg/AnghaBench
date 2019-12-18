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

__attribute__((used)) static const char* Range_Description(void) {
  return
    "The `Range` type is a basic iterable which acts as a virtual "
    "sequence of integers, starting from some value, stopping at some value "
    "and incrementing by some step."
    "\n\n"
    "This can be a useful replacement for the standard C `for` loop with "
    "decent performance but returning a Cello `Int`. It is constructable on "
    "the stack with the `range` macro which makes it practical and easy to "
    "use.";
}