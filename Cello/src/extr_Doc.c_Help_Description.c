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

__attribute__((used)) static const char* Help_Description(void) {
  return
    "The `Help` class can be implemented to let an object provide helpful "
    "information about itself. In the standard library this class is "
    "implemented by `Type` and it prints out the documentation provided "
    "by the `Doc` class in a friendly way.";
}