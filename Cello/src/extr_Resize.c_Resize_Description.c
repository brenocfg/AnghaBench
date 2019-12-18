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

__attribute__((used)) static const char* Resize_Description(void) {
  return
    "The `Resize` class can be implemented by objects which can be resized in "
    "some way. Resizing to a larger size than the current may allow for some "
    "resource or other to be preallocated or reserved. For example this class "
    "is implemented by `Array` and `Table` to either remove a number of items "
    "quickly or to preallocate memory space if it is known that many items are "
    "going to be added at a later date.";
}