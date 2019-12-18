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

__attribute__((used)) static const char* Push_Description(void) {
  return ""
    "The `Push` class provides an interface for the addition and removal of "
    "objects from another in a positional sense."
    "\n\n"
    "`push` can be used to add new objects to a collection and `pop` to remove "
    "them. Usage of `push` can require `assign` to be defined on the argument.";
}