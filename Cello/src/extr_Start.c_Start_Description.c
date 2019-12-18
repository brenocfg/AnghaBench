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

__attribute__((used)) static const char* Start_Description(void) {
  return
    "The `Start` class can be implemented by types which provide an abstract "
    "notion of a started and stopped state. This can be real processes such "
    "as `Thread`, or something like `File` where the on/off correspond to "
    "if the file is open or not."
    "\n\n"
    "The main nicety of the `Start` class is that it allows use of the `with` "
    "macro which performs the `start` function at the opening of a scope block "
    "and the `stop` function at the end.";
}