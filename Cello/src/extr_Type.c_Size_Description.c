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

__attribute__((used)) static const char* Size_Description(void) {
  return
    "The `Size` class is a very important class in Cello because it gives the "
    "size in bytes you can expect an object of a given type to be. This is "
    "used by many methods to allocate, assign, or compare various objects."
    "\n\n"
    "By default this size is automatically found and recorded by the `Cello` "
    "macro, but if the type does it's own allocation, or the size cannot be "
    "found naturally then it may be necessary to override this method.";
}