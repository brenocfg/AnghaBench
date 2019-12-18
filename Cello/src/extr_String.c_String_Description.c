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

__attribute__((used)) static const char* String_Description(void) {
  return
    "The `String` type is a wrapper around the native C string type. This "
    "includes strings that are allocated on either the Stack or the Heap."
    "\n\n"
    "For strings allocated on the heap a number of extra operations are "
    "provided overs standard C strings such as concatenation.";
}