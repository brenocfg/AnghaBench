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

__attribute__((used)) static const char* Box_Description(void) {
  return
    "The `Box` type is another wrapper around a C pointer with one additional "
    "behaviour as compared to `Ref`. When a `Box` object is deleted it will "
    "also call `del` on the object it points to. The means a `Box` is "
    "considered a pointer type that _owns_ the object it points to, and so is "
    "responsible for it's destruction. Due to this `Box`s must point to valid "
    "Cello objects and so can't be initalised with `NULL` or anything else "
    "invalid. "
    "\n\n"
    "While this might not seem that useful when there is Garbage Collection "
    "this can be very useful when Garbage Collection is turned off, and when "
    "used in conjunction with collections.";
}