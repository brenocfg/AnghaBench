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

__attribute__((used)) static const char* Get_Description(void) {
  return
    "The `Get` class provides a method to _get_ or _set_ certain properties "
    "of an object using keys and value. Typically it is implemented by "
    "data lookup structures such as `Table` or `Map` but it is also used "
    "more generally such as using indices to look up items in `Array`, or "
    "as thread local storage for the `Thread` object.";
}