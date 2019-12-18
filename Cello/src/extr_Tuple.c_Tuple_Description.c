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

__attribute__((used)) static const char* Tuple_Description(void) {
  return
    "The `Tuple` type provides a basic way to create a simple collection of "
    "objects. Its main use is the fact that it can be constructed on the "
    "stack using the `tuple` macro. This makes it suitable for a number of "
    "purposes such as use in functions that take a variable number of "
    "arguments."
    "\n\n"
    "Tuples can also be constructed on the heap and stored in collections. "
    "This makes them also useful as a simple _untyped_ list of objects."
    "\n\n"
    "Internally Tuples are just an array of pointers terminated with a pointer "
    "to the Cello `Terminal` object. This makes positional access fast, but "
    "many other operations slow including iteration and counting the number of "
    "elements. Due to this it is only recommended Tuples are used for small "
    "collections. "
    "\n\n"
    "Because Tuples are terminated with the Cello `Terminal` object this can't "
    "naturally be included within them. This object should therefore only be "
    "returned from iteration functions.";
}