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

__attribute__((used)) static const char* Copy_Description(void) {
  return
    "The `Copy` class can be used to override the behaviour of an object when "
    "a copy is made of it. By default the `Copy` class allocates a new empty "
    "object of the same type and uses the `Assign` class to set the "
    "contents. The copy is then registered with the Garbage Collector as if it "
    "had been constructed with `new`. This means when using manual memory "
    "management a copy must be deleted manually."
    "\n\n"
    "If the `copy` class is overridden then the implementer may manually have "
    "to register the object with the Garbage Collector if they wish for it to "
    "be tracked."
    "\n\n"
    "By convention `copy` follows the semantics of `Assign`, which typically "
    "means a _deep copy_ should be made, and that an object will create a "
    "copy of all of the sub-objects it references or contains - although this "
    "could vary depending on the type's overridden behaviours.";
}