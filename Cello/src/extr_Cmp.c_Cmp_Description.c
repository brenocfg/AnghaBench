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

__attribute__((used)) static const char* Cmp_Description(void) {
  return
    "The `Cmp` class is used to define comparison between two object values. "
    "This class is important as it is used by many data structures to test "
    "equality or ordering of objects."
    "\n\n"
    "By default, if passed two objects of the same type, the `Cmp` class will "
    "simply compare the raw memory of both objects, using the `Size` "
    "class."
    "\n\n"
    "To implement this class a `cmp` function must be provided which returns "
    "`< 0` if the first object is _less than_ the second, `> 0` if the first "
    "object is _greater than_ the second, and `0` if they are _equal_. "
    "\n\n"
    "For objects that manage their own data this class may need to be "
    "overridden to ensure that objects of the same _value_ are still treated "
    "as equal. E.G. for string types."
    "\n\n"
    "This class to used to test for _value_ equality between objects, I.E. if "
    "they represent the same thing. For _object_ equality the `is` keyword can "
    "be used, which will return `true` only if two variables are pointing to "
    "the same object in memory.";
}