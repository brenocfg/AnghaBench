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

__attribute__((used)) static const char* Show_Description(void) {
  return
    "The `Show` class is used to convert objects to, and from, a `String` "
    "representation. Objects which implement `Show` should expect the "
    "input/output object to be one that support the `Format` class, such as "
    "`File` or `String`."
    "\n\n"
    "The `print`, `println` and `print_to` functions provide a mechanism for "
    "writing formatted strings with Cello objects. To do this they provide a "
    "new format specifier `%$` which uses an object's `Show` functionality to "
    "write that part of the string. All objects which don't support `Show` can "
    "still be shown via a default implementation."
    "\n\n"
    "All the Show methods which are variable arguments only take `var` objects "
    "as input. To print native C types wrap them in Cello types using `$`."
    "\n\n"
    "Standard format specifiers such as `%f` and `%d` will call functions such "
    "as `c_float` and `c_int` on their passed arguments to convert objects to "
    "C types before performing the standard C formatting behaviour."
    "\n\n"
    "See [printf](http://www.cplusplus.com/reference/cstdio/printf/) for more "
    "information on format specifiers.";
}