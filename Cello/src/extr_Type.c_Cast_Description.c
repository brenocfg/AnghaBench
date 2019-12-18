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

__attribute__((used)) static const char* Cast_Description(void) {
  return
    "The `Cast` class provides a rudimentary run-time type checking. By "
    "default it simply checks that the passed in object is of a given type "
    "but it can be overridden by types which have to do more complex checking "
    "to ensure the types are correct.";
}