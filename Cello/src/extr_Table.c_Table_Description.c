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

__attribute__((used)) static const char* Table_Description(void) {
  return
    "The `Table` type is a hash table data structure that maps keys to values. "
    "It uses an open-addressing robin-hood hashing scheme which requires "
    "`Hash` and `Cmp` to be defined on the key type. Keys and values are "
    "copied into the collection using the `Assign` class and intially have "
    "zero'd memory."
    "\n\n"
    "Hash tables provide `O(1)` lookup, insertion and removal can but require "
    "long pauses when the table must be _rehashed_ and all entries processed."
    "\n\n"
    "This is largely equivalent to the C++ construct "
    "[std::unordered_map](http://www.cplusplus.com/reference/unordered_map/unordered_map/)";
}