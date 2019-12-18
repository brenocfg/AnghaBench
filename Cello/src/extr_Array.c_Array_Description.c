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

__attribute__((used)) static const char* Array_Description(void) {
  return ""
    "The `Array` type is data structure containing a sequence of a single type "
    "of object. It can dynamically grow and shrink in size depending on how "
    "many elements it contains. It allocates storage for the type specified. "
    "It also deallocates and destroys the objects inside upon destruction."
    "\n\n"
    "Elements are copied into an Array using `assign` and will initially have "
    "zero'd memory."
    "\n\n"
    "Elements are ordered linearly. Elements are accessed by their position in "
    "this sequence directly. Addition and removal of elements at the end of "
    "the sequence is fast, with memory movement required for elements in the "
    "middle of the sequence." 
    "\n\n"
    "This is largely equivalent to the C++ construct "
    "[std::vector](http://www.cplusplus.com/reference/vector/vector/)";
}