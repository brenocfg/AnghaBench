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

__attribute__((used)) static const char* Alloc_Description(void) {
  return
    "The `Alloc` class can be used to override how memory is allocated for a "
    "given data type. By default memory is allocated using `calloc` along with "
    "the `Size` class to determine the amount of memory to allocate."
    "\n\n"
    "A custom allocator should be careful to also initialise the header for "
    "the allocated memory using the function `header_init`. Cello objects "
    "without a header wont be recognised as such as so will throw errors when "
    "used with Cello functions."
    "\n\n"
    "Allocated memory is automatically registered with the garbage collector "
    "unless the functions `alloc_raw` and `dealloc_raw` are used."
  ;
}